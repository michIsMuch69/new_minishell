/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:04:48 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/28 14:55:35 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "libft.h"

// ###### INCLUDES ######

char	*final_build(char *token, char c)
{
	size_t	i;
	size_t	size;
	char	*final;

	i = 0;
	size = 0;
	while (token[i])
	{
		if (token[i] != c)
			size++;
		i++;
	}
	final = ft_calloc(sizeof(char), (size + 1));
	if (!final)
		return (NULL);
	i = 0;
	size = 0;
	while (token[i])
	{
		while(token[i] && token[i] != c)
		{
			final[size] = token[i];
			size++;
			i++;
		}
		i++;
	}
	return (final);
}

int	include_expand(char *token) //return the $ sign position
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

size_t	expand_token(char *prompt, char c, size_t *i)
{
	while (prompt[++(*i)])
	{
		if (prompt[*i] == c)
			return (++(*i));
	}
	return (++(*i));
}
