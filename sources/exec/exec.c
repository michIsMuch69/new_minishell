/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/07 10:30:36 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*skip_redir_symbol(int i, t_data *data)
{
	// if plus de 2 chevrons --> return -1
	// else return nb de char of file
	printf("file avant ==== %s\n", data[i].output.tab[0]);
	char	*file;
	
	file = malloc((ft_strlen(data[i].output.tab[0]) - 1) * sizeof(char));	
	file = ft_strcpy(file, &(data[i].output.tab[0][1]));
	
	printf("file apres ==== %s\n", file);
	return (file);

}

int	handle_child(int i, int fds[2], int tab_size, int prev_fd, t_data *data)
{
	
	int	input_fd; 
	int	output_fd;

	char *output_file = skip_redir_symbol(i, data);
	printf("outputfile in handle_child = %s\n", output_file);
	if (data[i].input.tab && data[i].input.tab[i])
	{
		input_fd = open(data[i].input.tab[0], O_RDONLY);
		if(dup2(input_fd, STDIN_FILENO))
			return (-1);
		close(input_fd);
	}
	else if (i > 0) //not first cmd.
	{
		if(dup2(prev_fd, STDIN_FILENO) == -1)
			return (-1); // --> proteger appel a pid, apres refacto);
		close(prev_fd);
	}
	if(data[i].output.tab && data[i].output.tab[i])
	{
		output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(dup2(output_fd, STDOUT_FILENO) == -1)
			return (-1);
		close(output_fd);
	}
	else if (i < tab_size - 1) // not last cmd.
	{
		if(dup2(fds[1], STDOUT_FILENO) == -1)
			return (-1);
		close(fds[1]);
	}
	// else
	// {
	// 	int	output_fd = open("file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	dup2(output_fd, STDOUT_FILENO);
	// }
	if (exec(i, data, tab_size) == -1)
		return (-1);
	close(fds[0]);
	return (0);
}

void	handle_parent(int i, int fds[2], int prev_fd, int tab_size)
{
	if (i > 0)
		close(prev_fd);
	if (i < tab_size)
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
			return (perror("pipe failed"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("fork failed"), -1);
		else if (pid == 0)
		{
			if (handle_child(i, fds, tab_size, prev_fd, data))
				return (-1);
		}
		else
		{
			handle_parent(i, fds, prev_fd, tab_size); //retour d'erreur ?
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
		return (perror("Failed to find directory"), -1);
	cmd_path = ft_concat_path(directory, data[i].args.tab[0]);
	if (!cmd_path)
		return (free(directory), -1);
	if (execve(cmd_path, data[i].args.tab, data[i].env.tab) == -1)
		return (perror("execve failed"), free(cmd_path), -1);
	return (0);
}
