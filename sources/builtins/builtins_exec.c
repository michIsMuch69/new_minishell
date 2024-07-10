/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/10 12:25:25 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_child(t_data *data, int tab_size, int i, int **fd)
{
	int	status;

	status = 0;
	if (ft_strcmp(data->args.tab[0], "pwd") == 0)
	{
		status = ft_pwd();
	}
	else if (ft_strcmp(data->args.tab[0], "echo") == 0)
	{
	    status = ft_echo(data->args.tab);
	}
	else if (ft_strcmp(data->args.tab[0], "env") == 0)
	{
	    status = ft_env(data->env.tab);
	}
	close_fds(data->in_out_fd);
	free_struct(data, tab_size);
	free_pipes(fd, tab_size - 1);
	exit(status);
}

int	exec_builtin_parent(t_data *data, int tab_size, int i, int **fd)
{
	if (ft_strcmp(data->args.tab[0], "cd") == 0)
		data[0].exit_status = ft_cd(data->args.tab, data->env.tab);
	else if (ft_strcmp(data->args.tab[0], "exit") == 0)
		ft_exit(data, tab_size, data->exit_status);
	else if (ft_strcmp(data->args.tab[0], "export") == 0)
		data[0].exit_status = ft_export(data->args.tab, data->env.tab);
	else if (ft_strcmp(data->args.tab[0], "unset") == 0)
	    data[0].exit_status = ft_unset(data->args.tab[1], &(data->env));
	close_fds(data[i].in_out_fd);
	return (data[0].exit_status);
}