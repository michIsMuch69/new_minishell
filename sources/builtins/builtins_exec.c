/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:39:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/09 10:11:00 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin_child(t_data *data, int **pipe_ptr, int tab_size)
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
	free_pipes(pipe_ptr, tab_size - 1);
	exit(status);
}

void	exec_builtin_parent(t_data *data, int tab_size)
{
	int	status;

	status = 0;
	if (ft_strcmp(data->args.tab[0], "cd") == 0)
	{
		printf("Executing built-in cd in parent process\n");

		status = ft_cd(data->args.tab, data->env.tab);
		if (status == -1)
			perror("cd failed");
		//close pipe free pipes
		return ;
		// cd doesn't exit the shell, so no exit(status) at the end.
	}
	else if (ft_strcmp(data->args.tab[0], "exit") == 0)
	{
		printf("Executing built-in exit in parent process\n");

		ft_exit(data, tab_size, data->exit_status);
		// close_fds(data->in_out_fd);
		// free_pipes(fd, tab_size);
		// free_struct(data, tab_size);
	}
	else if (ft_strcmp(data->args.tab[0], "export") == 0)
	{
	    status = ft_export(data->args.tab, data->env.tab);
	    return;  // cd doesn't exit the shell, so no exit(status) at the end.
	}
	else if (ft_strcmp(data->args.tab[0], "unset") == 0)
	{
	    status = ft_unset(data->args.tab[1], &(data->env));
	    return;  // cd doesn't exit the shell, so no exit(status) at the end.
	}
	// only exit the shell if the exit command is called
	// if errror : free_pipes structure close_fds  
	exit(status);
}