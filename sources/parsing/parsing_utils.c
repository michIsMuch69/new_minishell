/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:04:48 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/13 17:08:51 by fberthou         ###   ########.fr       */
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

int	include_char(char *token, char c, int start)
{
	while (token[start])
	{
		if (token[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

char	*init_str(char *token, char c)
{
	size_t	i;
	size_t	size;
	char	*final;

	i = 0;
	size = 0;
	if (!token)
		return (NULL);
	while (token[i])
	{
		if (token[i++] != c)
			size++;
	}
	final = ft_calloc(sizeof(char), (size + 1));
	if (!final)
		ft_perror("error -> malloc final_build\n");
	return (final);
}

char	*final_build(char *token, char c)
{
	size_t	i;
	size_t	size;
	char	*final;

	i = 0;
	size = 0;
	final = init_str(token, c);
	if (!final)
		return (NULL);
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

void	clear_buff(char *buffer, int start, int size)
{
	while (start < size)
		buffer[start++] = '\0';
}

size_t	find_end(char *prompt, char c, size_t *i)
{
	if (c == '<' || c == '>' || c == '$')
	{
		while (prompt[*i] && prompt[*i] != 32 && prompt[*i] != 9)
			(*i)++;
		return (*i);
	}
	while (prompt[++(*i)])
	{
		if (prompt[*i] == c || prompt[*i] == '<' || \
			prompt[*i] == '>' || prompt[*i] == '|')
			return (*i);
	}
	return (*i);
}
