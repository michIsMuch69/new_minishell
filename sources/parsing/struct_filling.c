/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/15 15:55:45 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "libft.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

void	print_struct(t_data *data, int tab_size);

// ###### PROTOTYPES ######

static enum e_rtype	find_type(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '|')
		return (PIPE);
	if (token[i] == '<')
	{
		while (token[i] && token[i] == '<')
			i++;
		if (i == 1)
			return (INPUT);
		else
			return (HEREDOC); // heredoc
	}
	if (token[i] == '>')
	{
		while (token[i] && token[i] == '>')
			i++;
		if (i == 1)
			return (OUTPUT);
		else
			return (APPEND);
	}
	else
		return (COMMAND);
}

bool	fill_tab(t_table *tab, char *token)
{
	char	**tmp;

	if (!tab->size)
	{
		tab->tab = ft_calloc(2, sizeof(char *));
		if (!tab->tab)
			return (ft_perror("error -> alloc struc arg tab\n"), 1);
	}
	else
	{
		tmp = ft_realloc(tab->tab, (sizeof(char *) * (tab->size + 2)), \
						(sizeof(char *) * (tab->size)));
		if (!tmp)
			return (ft_perror("error -> realloc args table\n"), 1);
		tmp[tab->size + 1] = NULL;
		tab->tab = tmp;
	}
	tab->tab[tab->size] = ft_strdup(token);
	if (!tab->tab[tab->size])
		return (ft_perror("error -> strdup\n"), 1);
	(tab->size)++;
	return (0);
}

bool	fill_struct(t_data *struc, t_table *tokens, int *i_tokens)
{
	if (struc->cmd_type == COMMAND)
	{
		if (fill_tab(&(struc->args), tokens->tab[*i_tokens]))
			return (1);
	}
	else if (struc->cmd_type == INPUT || struc->cmd_type == HEREDOC)
	{
		if (fill_tab(&(struc->input), tokens->tab[*i_tokens]))
			return (1);
	}
	else if (struc->cmd_type == OUTPUT || struc->cmd_type == APPEND)
	{
		if (fill_tab(&(struc->output), tokens->tab[*i_tokens]))
			return (1);
	}
	(*i_tokens)++;	
	return (0);
}

int	init_struct(t_data **data, t_table *tokens, int i_tokens, int i_data)
{
	t_data			*tmp;
	enum e_rtype	type;

	while (i_tokens < tokens->size)
	{
		type = find_type(tokens->tab[i_tokens]);
		if (type == PIPE) // if pipe is the first token -> syntax error
		{
			tmp = ft_realloc(*data, (sizeof(t_data) * (i_data + 2)), \
							(sizeof(t_data) * (i_data + 1))); //realloc_tab(*data);
			if (!tmp)
				return (ft_perror("error-> realloc struc tab\n"), -1);
			tmp[i_data + 1].env = tmp[0].env;
			*data = tmp;
			return (init_struct(data, tokens, ++i_tokens, ++i_data)); // realloc tab + 1 + recall fill_struct
		}
		else
		{
			(*data)[i_data].cmd_type = type;
			if (fill_struct(&(*data)[i_data], tokens, &i_tokens) == 1)
				return (-1);
		}
	}
	return (i_data + 1);
}
