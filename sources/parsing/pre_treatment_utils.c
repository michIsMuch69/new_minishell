/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_treatment_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:32:21 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/14 11:05:16 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	clear_buff(char *buffer, int start, int size);

// ###### PROTOTYPES ######

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && (str[*i] == 32 || str[*i] == 9))
		(*i)++;
}

char	*init_treatment(char *prompt, int *i_tmp, int i_prompt)
{
	char	*tmp;

	*i_tmp = i_prompt;
	tmp = ft_calloc(ft_strlen(prompt) + 3, sizeof(char));
	if (!tmp)
		return (free(prompt), ft_perror("error-> init pre_treatment\n"), NULL);
	tmp = ft_memcpy(tmp, prompt, ft_strlen(prompt));
	return (tmp);
}

int	filter(int *i, int i_tmp, char *str, char *tmp)
{
	int	f_index;

	skip_spaces(str, i);
	if (str[*i] == '$')
	{
		tmp[i_tmp] = str[*i];
		i_tmp++;
		(*i)++;
	}
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && str[*i] != '|' && \
			str[*i] != '$' && str[*i] != 9 && str[*i] != 32)
	{
		tmp[i_tmp] = str[(*i)++];
		i_tmp++;
	}
	tmp[i_tmp] = 32;
	f_index = i_tmp++;
	while (str[*i])
	{
		tmp[i_tmp] = str[(*i)++];
		i_tmp++;
	}
	clear_buff(tmp, i_tmp, (ft_strlen(str) + 3));
	return (f_index);
}
