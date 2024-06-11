/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_treatment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:51:51 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/06 14:59:07 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	clear_buff(char *buffer, size_t start, size_t size);

// ###### PROTOTYPES ######

static char	*init_treatment(char *prompt, size_t *i_tmp, size_t i_prompt)
{
	char	*tmp;

	*i_tmp = i_prompt;
	tmp = ft_calloc(ft_strlen(prompt) + 3, sizeof(char));
	if (!tmp)
		return (free(prompt), ft_perror("error-> init pre_treatment\n"), NULL);
	tmp = ft_memcpy(tmp, prompt, ft_strlen(prompt));
	return (tmp);
}

static char	*pipe_treatment(char *prompt, size_t *i_prompt, char c)
{
	char	*tmp;
	size_t	i_tmp;
	size_t	f_index;

	tmp = init_treatment(prompt, &i_tmp, *i_prompt);
	if (!tmp)
		return (NULL);
	tmp[i_tmp++] = 32;
	tmp[i_tmp++] = '|';
	tmp[i_tmp++] = 32;
	f_index = i_tmp;
	(*i_prompt)++;
	while (prompt[*i_prompt] && \
			(prompt[*i_prompt] == 32 || prompt[*i_prompt] == 9))
		(*i_prompt)++;
	while (prompt[(*i_prompt)])
	{
		tmp[i_tmp] = prompt[(*i_prompt)++];
		i_tmp++;
	}
	*i_prompt = f_index;
	clear_buff(tmp, i_tmp, (ft_strlen(prompt) + 3));
	return (free(prompt), tmp);
}

static size_t	filter(size_t *i_prompt, size_t i_tmp, char *prompt, char *tmp)
{
	size_t	f_index;

	while (prompt[*i_prompt] && \
			(prompt[*i_prompt] == 32 || prompt[*i_prompt] == 9))
		(*i_prompt)++;
	while (prompt[*i_prompt] && prompt[*i_prompt] != '<' && \
			prompt[*i_prompt] != '>' && prompt[*i_prompt] != '|' && \
			prompt[*i_prompt] != 9 && prompt[*i_prompt] != 32)
	{
		tmp[i_tmp] = prompt[(*i_prompt)++];
		i_tmp++;
	}
	tmp[i_tmp] = 32;
	f_index = i_tmp++;
	while (prompt[*i_prompt])
	{
		tmp[i_tmp] = prompt[(*i_prompt)++];
		i_tmp++;
	}
	clear_buff(tmp, i_tmp, (ft_strlen(prompt) + 3));
	return (f_index);
}

static char	*redir_treatment(char *prompt, size_t *i_prompt, char c)
{
	char	*tmp;
	size_t	i_tmp;

	tmp = init_treatment(prompt, &i_tmp, *i_prompt);
	if (!tmp)
		return (NULL);
	tmp[i_tmp++] = 32;
	while (prompt[*i_prompt] && prompt[*i_prompt] == c)
	{
		tmp[i_tmp] = prompt[(*i_prompt)++];
		i_tmp++;
	}
	*i_prompt = filter(i_prompt, i_tmp, prompt, tmp);
	return (free(prompt), tmp);
}

char	*pre_treatment(char *prompt)
{
	size_t	i_prompt;

	i_prompt = 0;
	while (prompt[i_prompt])
	{
		if (prompt[i_prompt] == '|')
		{
			prompt = pipe_treatment(prompt, &i_prompt, prompt[i_prompt]);
			if (!prompt)
				return (NULL);
		}
		else if (prompt[i_prompt] == '<' || prompt[i_prompt] == '>')
		{
			prompt = redir_treatment(prompt, &i_prompt, prompt[i_prompt]);
			if (!prompt)
				return (NULL);
		}
		else
			i_prompt++;
	}
	return (prompt);
}
