/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:56:02 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/29 15:44:33 by fberthou         ###   ########.fr       */
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

void	free_struct(t_data *ptr, size_t tab_size)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (i < tab_size)
	{
		if (ptr[i].cmd)
			free(ptr[i].cmd);
		if (ptr[i].opt)
			while (ptr[i].opt[y])
				free(ptr[i].opt[y++]);
		y = 0;
		if (ptr[i].args)
			while (ptr[i].args[y])
				free(ptr[i].args[y++]);
		i++;
	}
	free(ptr);
}

void	free_all(t_table tab, t_data *ptr, size_t ptr_size)
{
	size_t	i;

	i = 0;
	if (ptr)
		free_struct(ptr, ptr_size);
	if (tab.tab)
	{
		i = 0;
		while (tab.tab[i])
			free(tab.tab[i++]);
		free(tab.tab);
		tab.tab = NULL;
	}
}
