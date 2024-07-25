/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/25 08:38:27 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin(t_data *data, int tab_size, int i, int **fd)
{
	int	status;

	status = 0;
	if (ft_strcmp(data[i].args.tab[0], "pwd") == 0)
		data[0].exit_status = ft_pwd();
	else if (ft_strcmp(data[i].args.tab[0], "echo") == 0)
		data[0].exit_status = ft_echo(&data[i]);
	else if (ft_strcmp(data[i].args.tab[0], "env") == 0)
		data[0].exit_status = ft_env(&data[i]);
    else if (ft_strcmp(data[i].args.tab[0], "cd") == 0)
        data[0].exit_status = ft_cd(&data[i]);
    else if (ft_strcmp(data[i].args.tab[0], "exit") == 0)
        ft_exit(&data[i], tab_size, data[i].exit_status);
    else if (ft_strcmp(data[i].args.tab[0], "export") == 0)
        data[0].exit_status = ft_export(&data[i], &data[i].export);
    else if (ft_strcmp(data[i].args.tab[0], "unset") == 0)
        data[0].exit_status = ft_unset(&data[i]);

    return (data[0].exit_status);
}
