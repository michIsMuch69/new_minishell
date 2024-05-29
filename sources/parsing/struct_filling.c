/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_filling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:41:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/29 18:00:22 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

// ###### PROTOTYPES ######

enum e_type find_type(t_table *tokens, size_t *i)
{
	
}

int	fill_struct(t_data **data, t_table *tokens, char **envp)
{
	size_t	tab_size;
	size_t	i_tab_arg;

	tab_size = 0;
	i_tab_arg = 0;
	// char *data annalyzer -> cmd_data.cmd_type = data_type(tab_token[i])
	
	data[tab_size]->cmd_type = find_type(tokens, &i_tab_arg);
	data[tab_size]->cmd = data;
	data[tab_size]->opt = NULL;
	data[tab_size]->args = NULL;
	data[tab_size]->infile = NULL;
	data[tab_size]->outfile = NULL;
	
	return (++tab_size);
}
