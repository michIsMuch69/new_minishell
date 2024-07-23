/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:46:39 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/23 08:31:21 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int exec_redirection(t_data data, int *fds, int last_read);

int exec_one_built(t_data *data, int tab_size, int i)
{
    if (ft_strcmp(data->args.tab[0], "pwd") == 0)
		data[i].exit_status = ft_pwd();
	else if (ft_strcmp(data->args.tab[0], "echo") == 0)
		data[i].exit_status = ft_echo(data);
	else if (ft_strcmp(data->args.tab[0], "env") == 0)
		data[i].exit_status = ft_env(data);
    else if (ft_strcmp(data[i].args.tab[0], "cd") == 0)
        data[i].exit_status = ft_cd(data);
    else if (ft_strcmp(data[i].args.tab[0], "exit") == 0)
        ft_exit(data, tab_size, data[i].exit_status);
    else if (ft_strcmp(data[i].args.tab[0], "export") == 0)
    {
		static t_table	export;
		
		if (!export.tab)
			init_exported_env(data, &export);
        if (data[i].args.tab[1] == NULL)
            data[i].exit_status = ft_export_print(&export);
        else
            data[i].exit_status = ft_export(data, &export);
    }
    else if (ft_strcmp(data[i].args.tab[0], "unset") == 0)
        data[i].exit_status = ft_unset(data);
    return (data[i].exit_status);
}

int parent_routine(t_data *data, int i, int tab_size, int **fd)
{
    int ret_value;

    if (fd)
    {
        if (i == 0)
            ret_value = close(fd[i][1]);
        else
        {
            ret_value = close(fd[i - 1][0]);
            if (i < tab_size - 1)
                ret_value = close(fd[i][1]);
        }
        if (ret_value)
            perror("close pipe in parent ");
    }
    ret_value = close_fds(data[i].in_out_fd);
    if (ret_value == -1)
        perror("close in_out files in parent ");
    return (ret_value);
}

static int child_routine(t_data *data, int tab_size, int i, int **fd)
{
    int ret_value;

    ret_value = manage_redirection(data, tab_size, i, fd);
    
    if (is_builtin(&data[i]))
    {
        exec_builtin(data, tab_size, i, fd);
        exit(data[i].exit_status);
    }
    // else
    // {
    //     if (execve(data[i].cmd_path, data[i].args.tab, data[i].env.tab) == -1)
    //         exit(EXIT_FAILURE);
    // }
    if (i == tab_size - 1 && fd)
    {
        if (close(fd[i - 1][0]) == -1)
            return (-1);
    }
    else if (fd)
    {
        if (i)
        {
            if (close_pipes(fd, (tab_size - 1), i, fd[i - 1][0]) == -1)
                return (-1);
        }
        else
        {
            if (close_pipes(fd, (tab_size - 1), i, 0) == -1)
                return (-1);
        }
    }
	return (ret_value);
}

static int	exec_all(t_data *data, int tab_size, int **fd)
{
    int     i;
	pid_t   pid;
    int     ret_value;

    i = -1;
    while (++i < data->tab_size)
	{
        if(is_builtin(&data[i]) && tab_size == 1)
            return (exec_one_built(data, tab_size, i));
        else
        {
            pid = fork();
            if (pid < 0)
                return (perror("Fork failed "), pid);  // -1 -> crash
            if (pid == 0)
            {	
                if (child_routine(data, tab_size, i, fd) == -1)
                    return (free_pipes(fd, tab_size -1), exit(1), 1);
                free_pipes(fd, tab_size - 1);
				if (!is_builtin(&data[i]))
					if (execve(data[i].cmd_path, data[i].args.tab, data[i].env.tab) == -1)
						exit(EXIT_FAILURE);
				exit(data[i].exit_status);
            }
            else if (pid > 0)
                if (parent_routine(data, i, tab_size, fd) == -1)
                    return (free_pipes(fd, tab_size - 1), -1);
        }
    }
    free_pipes(fd, tab_size - 1);
    return (wait_all(data, tab_size, pid));
}

int exec(int tab_size, t_data *data)
{
    int ret_value;
    int **pipe_fd;
    int i;

    i = -1;
    ret_value = init_exec(data, tab_size);
    if (ret_value)
    {
        while (++i < tab_size)
            close_fds(data[i].in_out_fd);
        return (ret_value);
    }
    if (tab_size == 1)
        ret_value = exec_all(data, tab_size, NULL);
    else
    {
        pipe_fd = init_pipe(data, tab_size - 1);
        if (!pipe_fd)
            return (-1);
        ret_value = exec_all(data, tab_size, pipe_fd);
    }
    return (ret_value);
}
