/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:56:02 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/14 10:38:25 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"
#include "struct.h"

// ###### INCLUDES ######

size_t	ft_perror(char *err_message)
{
	return (write(2, err_message, ft_strlen(err_message)));
}

void	free_tab(t_table tab)
{
	int	i;

	i = 0;
	if (!tab.tab)
		return ;
	while (i < tab.size)
		free(tab.tab[i++]);
	free(tab.tab);
}

void	free_struct(t_data *struc, size_t tab_size)
{
	size_t	i;

	i = 0;
	while (i < tab_size)
	{
		if (struc[i].cmd_path)
		{
			free(struc[i].cmd_path);
			struc[i].cmd_path = NULL;
		}
		free_tab(struc[i].args);
		struc[i].args.tab = NULL;
		free_tab(struc[i].input);
		struc[i].input.tab = NULL;
		free_tab(struc[i].output);
		struc[i].output.tab = NULL;
		i++;
	}
	free_tab(struc[0].env);
	free(struc);
}
