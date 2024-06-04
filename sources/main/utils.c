/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:56:02 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/31 17:45:54 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"
#include "struct.h"

// ###### INCLUDES ######

size_t	ft_perror(char *err_message)
{
	return(write(2, err_message, ft_strlen(err_message)));
}

void	free_tab(char **tab, int tab_size)
{
	int	i;

	i = 0;
	if (!tab)
		return;
	while (i < tab_size)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

void	free_lst(t_redir *lst)
{
	printf("free redir == problem\n");
	return ;
}

void	free_struct(t_data *struc, size_t tab_size)
{
	size_t	i;

	i = 0;
	while (i < tab_size)
	{
		if (struc[i].cmd)
			free(struc[i].cmd);
		if (struc[i].args.tab)
			free_tab(struc[i].args.tab, struc[i].args.size);
		if (struc[i].env.tab && i == 0)
			free_tab(struc[i].env.tab, struc[i].env.size);
		if (struc->redir)
			free_lst(struc->redir);
		i++;
	}
	free(struc);
}
