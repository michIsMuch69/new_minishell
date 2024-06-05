/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/05 09:43:04 by fberthou         ###   ########.fr       */
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
void	free_tab(t_table tab);
void	free_struct(t_data *struc, size_t tab_size);

void	print_struct(t_data *data, int tab_size);

// ###### PROTOTYPES ######

// static enum e_rtype	redir_type(char *token)
// {
// 	return (INFILE);
// }

static t_data	*realloc_tab(t_data *data)
{
	return (data);
}

// static t_redir	*redir_management(t_table *tokens, size_t *start)
// {
// 	return (NULL);
// }

static enum e_rtype	find_type(char *token)
{
	if (token[0] == '|')
		return (PIPE);
	else
		return (COMMAND);
}

size_t	find_size(t_table tokens, int i_tokens)
{
	size_t	size;

	size = 0;
	while (tokens.tab[i_tokens] && find_type(tokens.tab[i_tokens]) == COMMAND)
	{
		size++;
		i_tokens++;
	}
	return (size);
}

bool	fill_struct(t_data *struc, t_table *tokens, size_t *i_tokens, size_t i_struc)
{
	size_t	tab_size;

	if (struc->cmd_type == COMMAND)
	{
		struc->args.size = 0;
		tab_size = find_size(*tokens, *i_tokens);
		struc->args.tab = ft_calloc((tab_size + 1), sizeof(char *));
		if (!struc->args.tab)
			return (ft_perror("error -> alloc struc arg tab\n"), 1);
		while (struc->args.size < tab_size)
		{
			struc->args.tab[struc->args.size] = ft_strdup(tokens->tab[*i_tokens]);
			if (!struc->args.tab[struc->args.size])
				return (ft_perror("error -> strdup\n"), 1);
			(struc->args.size)++;
			(*i_tokens)++;
		}
	}
	return (0);
}


int	init_table(t_data **data, t_table *tokens, size_t i_tokens, size_t i_data)
{
	t_data			*tmp;
	enum e_rtype	type;

	while (i_tokens < tokens->size)
	{
		type = find_type(tokens->tab[i_tokens]);
		if (type == PIPE) // if pipe is the first token -> syntax error
		{
			tmp = ft_realloc(*data, (sizeof(t_data) * (i_data + 2)), (sizeof(t_data) * (i_data + 1))); //realloc_tab(*data);
			if (!tmp)
				return (ft_perror("error -> realloc\n"), free_struct(*data, i_data + 1), -1);
			tmp[i_data + 1].env = tmp[0].env;
			*data = tmp;
			return (init_table(data, tokens, ++i_tokens, ++i_data)); // realloc tab + 1 + recall fill_struct
		}
		else
		{
			(*data)[i_data].cmd_type = type;
			if (fill_struct(&(*data)[i_data], tokens, &i_tokens, i_data) == 1)
				return (free_struct(*data, i_data + 1), -1);
		}
	}
	return (i_data + 1);
}
