/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 11:35:51 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"

// ###### INCLUDES ######


// ###### PROTO ######

size_t	ft_perror(char *err_message);

void	print_struct(t_data *data, int tab_size);
void	print_tab(t_table tab);

// ###### PROTO ######


int		exec(t_data *data, int tab_size)
{
	if (!data)
		return (-1);
	print_struct(data, tab_size);
	return (0);
}