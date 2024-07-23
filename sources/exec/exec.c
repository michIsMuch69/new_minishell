/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 08:46:39 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/23 07:46:18 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int exec_redirection(t_data data, int *fds, int last_read);

int parent_routine(t_data *data, int i, int tab_size, int **fd)
{
    int ret_value;

    if (fd)
    {
        if (i == 0)
        {
            print_fd_operation("Parent close", fd[i][1]);
            ret_value = close(fd[i][1]);
        }
        else
        {
            print_fd_operation("Parent close", fd[i - 1][0]);
            ret_value = close(fd[i - 1][0]);
            if (i < tab_size - 1)
            {
                print_fd_operation("Parent close", fd[i][1]);
                ret_value = close(fd[i][1]);
            }
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

    ret_value = 0;
    if (i < tab_size - 1 && fd)
    {
        if (i)
        {
            print_fd_operation("child redirect", fd[i - 1][0]);
            ret_value = exec_redirection(data[i], fd[i], fd[i - 1][0]);
        }
        else
        {
            print_fd_operation("child redirect", 0);
            ret_value = exec_redirection(data[i], fd[i], 0);
        }
    }
    else if (fd)
    {
        print_fd_operation("child redirect", fd[i - 1][0]);
        ret_value = exec_redirection(data[i], NULL, fd[i - 1][0]);
    }
    else
    {
        print_fd_operation("child redirect", 0);
        ret_value = exec_redirection(data[i], NULL, 0);
    }

    if (is_builtin(&data[i]))
    {
        exec_builtin(data, tab_size, i, fd);
        exit(data[i].exit_status);
    }
    else
    {
        if (execve(data[i].cmd_path, data[i].args.tab, data[i].env.tab) == -1)
            exit(EXIT_FAILURE);
    }

    if (i == tab_size - 1 && fd)
    {
        print_fd_operation("Child close", fd[i - 1][0]);
        if (close(fd[i - 1][0]) == -1)
            return (-1);
    }
    else if (fd)
    {
        if (i)
        {
            print_fd_operation("Child close", fd[i - 1][0]);
            if (close_pipes(fd, (tab_size - 1), i, fd[i - 1][0]) == -1)
                return (-1);
        }
        else
        {
            print_fd_operation("Child close", 0);
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
            exec_builtin(data, tab_size, i, fd);
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
				printf("cmdpath == %s\n", data[i].cmd_path);
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

        print_fd_array(pipe_fd, tab_size - 1, "Initial state of pipe_fd");

        ret_value = exec_all(data, tab_size, pipe_fd);
    }
    return (ret_value);
}
