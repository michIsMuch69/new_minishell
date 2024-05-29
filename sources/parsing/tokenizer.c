/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:10:46 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/29 15:38:40 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <stdlib.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	free_all(char **tab, t_data *ptr, size_t tab_size);
size_t	expand_token(char *prompt, char c, size_t *i);

// ###### PROTOTYPES ###### 


static int	build_token(char *prompt, size_t start, size_t end, t_table *token)
{
	size_t			i;
	size_t			tok_size;

	i = 0;
	tok_size = end - start;
	token->tab[token->size] = ft_calloc(sizeof(char), tok_size + 1);
	if (!token->tab[token->size])
		return (ft_perror("error -> token memory allocation\n"), -1);
	while (i < tok_size)
	{
		token->tab[token->size][i] = prompt[start];
		i++;
		start++;
	}
	return (1);
}

static int	extract_expand_token(char *prompt, size_t *i, t_table *token)
{
	size_t	start;

	start = *i;
	(*i)++;
	if (prompt[*i] == '\'')
		return (build_token(prompt, start, \
				expand_token(prompt, '\'', i), token));
	else if (prompt[*i] == '"')
		return (build_token(prompt, start, \
				expand_token(prompt, '"', i), token));
	else if (prompt[*i] == '{')
		return (build_token(prompt, start, \
				expand_token(prompt, '}', i), token));
	else
		return (build_token(prompt, start, \
				expand_token(prompt, ' ', i), token));
}

static int	extract_token(char *prompt, size_t *i, char c, t_table *token)
{
	size_t	start;

	start = *i;
	if (c == '\'' || c == '"')
	{
		while (prompt[++(*i)])
		{
			if (prompt[*i] == c && (prompt[*i + 1] == ' ' || !prompt[*i + 1]))
				return (build_token(prompt, start, ++(*i), token));
			else
				(*i)++;
		}
		return (build_token(prompt, start, *i, token));
	}
	else if (c == '$')
		return (extract_expand_token(prompt, i, token));
	else
	{
		(*i)++;
		while (prompt[*i] && prompt[*i] != ' ')
			(*i)++;
		return (build_token(prompt, start, *i, token));
	}
	return (0);
}

static int	split_tokens(char *prompt, size_t *i, t_table *token)
{
	size_t	start;

	while (prompt[*i] == ' ' || (prompt[*i] >= '\t' && prompt[*i] <= '\r'))
		(*i)++;
	while (prompt[*i])
	{
		if (prompt[*i] == '\'')
			return (extract_token(prompt, i, '\'', token));
		else if (prompt[*i] == '"')
			return (extract_token(prompt, i, '"', token));
		else if (prompt[*i] == '$')
			return (extract_token(prompt, i, '$', token));
		else
			return (extract_token(prompt, i, 0, token));
		(*i)++;
	}
	return (0);
}

t_table	tokenizer(char *prompt)
{
	size_t	i;
	t_table	token;
	char	**tmp;
	int		ret_value;

	i = 0;
	token.size = 0;
	token.tab = ft_calloc(sizeof(char *), 1);
	if (!token.tab)
		return (ft_perror("error -> token memory allocation\n"), token);
	while (prompt[i])
	{
		ret_value = split_tokens(prompt, &i, &token);
		if (ret_value == -1)
			return (free_all(token.tab, NULL, 0), token.size = 0, token); // free_all must have tab_size
		if (!ret_value)
			break ;
		tmp = ft_realloc(token.tab, ((token.size + 2) * sizeof(char *)), \
									((token.size + 1) * sizeof(char *)));
		if (!tmp)
			return (free_all(token.tab, NULL, 0), ft_perror("error -> tab_arg memory allocation\n"), token.size = 0, token);
		token.tab = tmp;
		(token.size)++;
	}
	return (token);
}
