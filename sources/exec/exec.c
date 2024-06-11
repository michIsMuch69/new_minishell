/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/11 13:47:58 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_child(int i, int *fds, int tab_size, int prev_fd, t_data *data)
{
	if (redir_input(data, i, prev_fd) == -1)
		return (-1);
	if (redir_output(data, i, tab_size, fds) == -1)
		return (-1);
	if (exec(i, data, tab_size) == -1)
		return (-1);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
// test : 
// -  cat < file2.txt | rev > file1.txt

void	handle_parent(int i, int *fds, int prev_fd, int tab_size)
{
	if (i > 0)
		close(prev_fd);
	close(fds[1]);
}

int	pipex(int tab_size, t_data *data)
{
	int		i;
	int		prev_fd;
	int		fds[2];
	pid_t	pid;

	prev_fd = 0;
	i = 0;
	while (i < tab_size)
	{
		if (pipe(fds) == -1)
			return (perror("Pipe failed"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("Fork failed"), -1);
		else if (pid == 0)
			handle_child(i, fds, tab_size, prev_fd, data);
		else
		{
			handle_parent(i, fds, prev_fd, tab_size);
			prev_fd = fds[0];
		}
		i++;
	}
	wait_all(tab_size);
	return (0);
}

int	exec(int i, t_data *data, int tab_size)
{
	char	*directory;
	char	*cmd_path;

	if (!data || !data[i].args.tab)
		return (perror("Data structure is not properly initalized"), -1);
	directory = check_all_dirs(data[i].args.tab[0]);
	if (!directory)
		return (perror("Command not found"), -1);
	cmd_path = ft_concat_path(directory, data[i].args.tab[0]);
	if (!cmd_path)
		return (free(directory), -1);
	//print_struct(data, tab_size);
	if (execve(cmd_path, data[i].args.tab, data[i].env.tab) == -1)
		return (perror("execve failed"), free(cmd_path), -1);
	return (0);
}
