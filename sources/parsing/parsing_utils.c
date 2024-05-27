/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:04:48 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/25 20:28:15 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	expand_token(char *prompt, char c, size_t *i)
{
	while (prompt[++(*i)])
	{
		if (prompt[*i] == c)
			return (++(*i));
	}
	return (++(*i));
}

void	free_tab(char **tab, size_t tab_size)
{
	size_t	i;

	i = 0;
	while (i < tab_size)
		free(tab[i++]);
	free(tab);
}
