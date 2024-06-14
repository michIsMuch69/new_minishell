/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:27:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/14 16:32:43 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "struct.h"
#include "libft.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

// main/utils.c
size_t	ft_perror(char *err_message);
void	free_tab(t_table tab, int start);

// parsing/expand_utils.c
int		count_sign(char *str, char sign);
int		change_value(char **token, char **envp);
int		cut_str(char **token, int start, int end);

// parsing/parsing_utils.c
int		include_char(char *token, char c, int start);

// ###### PROTOTYPES ######

//int	args_management()

int	file_management(t_table *file, char **envp)
{
	int	i_tab;
	int	ret_value;

	i_tab = 0;
	while (i_tab < file->size)
	{
		if (include_char(file->tab[i_tab], '$', 0) != -1)
		{
			if (count_sign(file->tab[i_tab], file->tab[i_tab][0]) < 2)
			{
				ret_value = change_value(&(file->tab[i_tab]), envp);
				if (ret_value == -1) // error malloc
					return (-1);
				if (ret_value == 1) // not in env
				{
					file->size = i_tab - 1;
					return (ft_perror("ambiguous redirect\n"), \
							free_tab(file[0], file->size), 0);
				}
			}
		}
		i_tab++;
	}
	return (0);
}

int	arg_management(t_table *file, char **envp)
{
	int	i_tab;
	int	ret_value;

	i_tab = 0;
	while (i_tab < file->size)
	{
		if (include_char(file->tab[i_tab], '$', 0) != -1 && \
			file->tab[i_tab][0] != '\'')
		{
			ret_value = change_value(&(file->tab[i_tab]), envp);
			while (ret_value)
			{
				if (ret_value == -1) // error malloc
					return (-1);
				if (ret_value == 1) // not in env
				{
					ret_value = cut_str(&(file->tab[i_tab]), 0, 0);
					if (ret_value == -1)
						return (-1);
				}
				ret_value = change_value(&(file->tab[i_tab]), envp);
			}
		}
		i_tab++;
	}
	return (0);
}

int	expand_management(t_data *data, char **envp)
{
	/*
		* args->tab -> 
			// simple quotes -> no changement
			// double quotes	-> change value if in env
								-> delete $NAME if is not in env
		
		* inputs :
			// if HEREDOC -> keep the litteral value
			// if $NAME is not in env -> ambiguous redirect -> clean tab
			// if $NAME is in env -> change the value
		
		* output :
			// if $NAME is not in env -> ambiguous redirect -> clean tab
			// if $NAME is in env -> change the value
	*/
	int	ret_value;

	ret_value = file_management(&(data->input), envp);
	if (ret_value == -1)
		return (-1);
	else if (ret_value == 1)
		return (1);
	ret_value = file_management(&(data->output), envp);
	if (ret_value == -1)
		return (-1);
	else if (ret_value == 1)
		return (1);
	ret_value = arg_management(&(data->args), envp);
	if (ret_value == -1)
		return (-1);
	else if (ret_value == 1)
		return (1);
	return (0);
}
