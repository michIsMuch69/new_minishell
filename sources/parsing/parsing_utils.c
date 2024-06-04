/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:04:48 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 13:49:09 by fberthou         ###   ########.fr       */
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

// ###### PROTOTYPES ######

char	*final_build(char *token, char c)
{
	size_t	i;
	size_t	size;
	char	*final;

	i = 0;
	size = 0;
	while (token[i])
	{
		if (token[i++] != c)
			size++;
	}
	final = ft_calloc(sizeof(char), (size + 1));
	if (!final)
		return (ft_perror("error -> malloc final_build\n"), NULL);
	i = 0;
	size = 0;
	while (token[i])
	{
		if (token[i] != c)
		{
			while(token[i] && token[i] != c)
			{
				final[size] = token[i];
				size++;
				i++;
			}
		}
		else
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

size_t	find_end(char *prompt, char c, size_t *i)
{
	while (prompt[++(*i)])
	{
		if (prompt[*i] == c)
			return (++(*i));
	}
	return (++(*i));
}
