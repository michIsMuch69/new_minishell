/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/31 17:44:45 by fberthou         ###   ########.fr       */
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
void	free_struct(t_data *struc, size_t tab_size);

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

bool	fill_struct(t_data *curr_struc, t_table *tokens, size_t *i_tokens)
{
	size_t	i;

	i = 0;
	curr_struc->cmd = ft_strdup(tokens->tab[(*i_tokens)++]);
	if (!curr_struc->cmd)
		return (1);
	while (*i_tokens < tokens->size)
	{
		if (find_type(tokens->tab[*i_tokens]) == PIPE)
			return (0);
		// else if (find_type(tokens->tab[*i_tokens]) != COMMAND)
		// 	redir_management(tokens, i_tokens);
		else
		{
			curr_struc->args.tab = ft_calloc((find_size(*tokens, *i_tokens) + 1), sizeof(char *));
			if (!curr_struc->args.tab)
				return (ft_perror("error -> alloc struct arg tab"), 1);
			while (*i_tokens < tokens->size && find_type(tokens->tab[*i_tokens]) == COMMAND)
			{
				curr_struc->args.tab[i] = ft_strdup(tokens->tab[*i_tokens]);
				if (!curr_struc->args.tab[i])
					return (ft_perror("error -> alloc struct arg tab"), 1); // !! maybe leak or double free
				if (!curr_struc->args.tab[i][0])
					return (0);
				i++;
				(*i_tokens)++;
			}
		}
		(*i_tokens)++;
	}
	curr_struc->args.size = (i + 1);
	return (0);
}

int	set_table(t_data **data, t_table *tokens, size_t i_tokens, size_t data_size)
{
	while (i_tokens < tokens->size)
	{
		data[data_size]->cmd_type = find_type(tokens->tab[i_tokens]);
		if (data[data_size]->cmd_type == PIPE) // if pipe is the first token -> syntax error
		{
			data[data_size] = realloc_tab(*data);
			if (!data[data_size])
				return (free_struct(*data, (data_size + 1)), ft_perror("error -> realloc\n") -1);
			data_size++;
			data[data_size]->env = data[0]->env;
			return (set_table(data, tokens, i_tokens, data_size)); // realloc tab + 1 + recall fill_struct
		}
		else
			if (fill_struct(data[data_size], tokens, &i_tokens) == 1)
				return (free_struct(*data, (data_size + 1)), -1);
	}
	return (data_size + 1);
}
