/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:10:46 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/27 09:09:42 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"
#include <stdlib.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	free_tab(char **tab, size_t tab_size);
size_t	expand_token(char *prompt, char c, size_t *i);

// ###### PROTOTYPES ######


static char	*build_token(char *prompt, size_t start, size_t end)
{
	char	*token;
	size_t	tok_size;
	size_t	i;

	i = 0;
	tok_size = end - start;
	token = ft_calloc(sizeof(char), tok_size + 1);
	if (!token)
		return (ft_perror("error -> token memory allocation\n"), NULL);
	while (i < tok_size)
	{
		token[i] = prompt[start];
		i++;
		start++;
	}
	return (token);
}

static char	*extract_expand_token(char *prompt, size_t *i)
{
	char	*token;
	size_t	start;

	start = *i;
	(*i)++;
	if (prompt[*i] == '\'')
		return (build_token(prompt, start, expand_token(prompt, '\'', i)));
	else if (prompt[*i] == '"')
		return (build_token(prompt, start, expand_token(prompt, '"', i)));
	else if (prompt[*i] == '{')
		return (build_token(prompt, start, expand_token(prompt, '}', i)));
	else
		return (build_token(prompt, start, expand_token(prompt, ' ', i)));
}

static char	*extract_token(char *prompt, size_t *i, char c)
{
	size_t	start;

	start = *i;
	if (c == '\'' || c == '"')
	{
		while (prompt[++(*i)])
		{
			if (prompt[*i] == c && (prompt[*i + 1] == ' ' || !prompt[*i + 1]))
				return (build_token(prompt, start, ++(*i)));
			else
				(*i)++;
		}
		return (build_token(prompt, start, *i));
	}
	else if (c == '$')
		return (extract_expand_token(prompt, i));
	else
	{
		(*i)++;
		while (prompt[*i] && prompt[*i] != ' ')
			(*i)++;
		return (build_token(prompt, start, *i));
	}
	return (NULL);
}

static char	*split_tokens(char *prompt, size_t *i)
{
	size_t	start;

	while (prompt[*i] == ' ' || (prompt[*i] >= '\t' && prompt[*i] <= '\r'))
		(*i)++;
	while (prompt[*i])
	{
		if (prompt[*i] == '\'')
			return (extract_token(prompt, i, '\''));
		else if (prompt[*i] == '"')
			return (extract_token(prompt, i, '"'));
		else if (prompt[*i] == '$')
			return (extract_token(prompt, i, '$'));
		else
			return (extract_token(prompt, i, 0));
		(*i)++;
	}
	return (NULL);
}

char	**tokenizer(char *prompt)
{
	size_t	i;
	size_t i_tab;
	char	**tab_arg;
	char	**realloc_protect;

	i = 0;
	i_tab = 0;

	tab_arg = ft_calloc(sizeof(char *), 1);
	if (!tab_arg)
		return (ft_perror("error -> tab_arg memory allocation\n"), NULL);
	while (prompt[i])
	{
		tab_arg[i_tab] = split_tokens(prompt, &i);
		if (!tab_arg[i_tab])
			break;
		realloc_protect = ft_realloc(tab_arg, ((i_tab + 2) * sizeof(char *)), \
									((i_tab + 1) * sizeof(char *)));
		if (!realloc_protect)
			return (free_tab(tab_arg, (i_tab + 1)), ft_perror("error -> tab_arg memory allocation\n"), NULL);
		tab_arg = realloc_protect;
		(i_tab)++;
	}
	return (tab_arg);
}
