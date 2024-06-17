/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:03:17 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/12 10:57:25 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

// ###### PROTOTYPES ######

char	*extract_word(char *str, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc((end - start) + 1, sizeof(char));
	if (!tmp)
		return (ft_perror("error-> alloc extract var\n"), NULL);
	while (start < end)
	{
		tmp[i] = str[start];
		i++;
		start++;
	}
	return (tmp);
}

// char	*find_var(char *word, char *str)
// {
// 	int	i_word;
// 	int	i_str;

// 	i_str = 0;
// 	i_word = 0;
// 	while (word[i_word] && str[i_str])
// 	{
// 		if (word[i_word] != str[i_str])
// 			return (NULL);
// 		i_word++;
// 		i_str++;
// 	}
// 	if (!word[i_word] && str[i_str] == '=')
// 		return (str);
// 	else
// 		return (NULL);
// }


static int	extract_value(char *var, char *word, char **var_content)
{
	size_t	i_var;
	size_t	i_content;

	i_content = 0;
	i_var = ft_strlen(word) + 1;
	var_content[0] = ft_calloc((ft_strlen(var) - ft_strlen(word)) + 1, \
															sizeof(char));
	if (!var_content[0])
		return (ft_perror("error-> alloc var_content\n"), -1);
	while (var[i_var])
	{
		var_content[0][i_content] = var[i_var];
		i_content++;
		i_var++;
	}
	return (0);
}

static char	*var_exist(char *word, char **env)
{
	size_t	i_env;
	size_t	i_word;
	size_t	i_str;

	i_str = 0;
	i_word = 0;
	i_env = 0;
	while (env[i_env])
	{
		while (word[i_word] && env[i_env][i_str])
		{
			if (word[i_word] != env[i_env][i_str++])
				break ;
			i_word++;
		}
		if (!word[i_word] && env[i_env][i_str] == '=')
			return (env[i_env]);
		i_env++;
		i_word = 0;
		i_str = 0;
	}
	return (NULL);
}

int	ft_getenv(char *word, char **env, char **var_content)
{
	char	*tmp;

	tmp = var_exist(word, env);
	if (!tmp)
		return (1);
	return (extract_value(tmp, word, var_content));
}