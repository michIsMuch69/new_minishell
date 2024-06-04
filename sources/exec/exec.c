/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 13:16:27 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include "struct.h"
#include <stddef.h>

// ###### INCLUDES ######


// ###### PROTO ######

size_t	ft_perror(char *err_message);

void	print_struct(t_data *data, int tab_size);
void	print_tab(t_table tab);

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	exec_found(const char *dirname, char *exec_searched)
{
	DIR				*dir;
	struct dirent	*entity;

	dir = opendir(dirname);
	if (!dir)
		return (-1);
	entity = readdir(dir);
	while (entity != NULL)
	{
		if (ft_strcmp(entity->d_name, exec_searched) == 0)
		{
			closedir(dir);
			return (1);
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (0);
}

char	*check_all_dirs(char *exec_searched)
{
	const char	*paths;
	char		**path_list;
	char		*result;
	int			i;

	paths = getenv("PATH");
	if (!paths)
		return (NULL);
	path_list = ft_split(paths, ':');
	result = NULL;
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		if (exec_found(path_list[i], exec_searched) == 1)
		{
			result = ft_strdup(path_list[i]);
			break ;
		}
		i++;
	}
	free_array(path_list);
	return (result);
}

char	*ft_concat_path(char *directory, char *prompt)
{
	size_t	total_length;
	char	*exec_path;

	total_length = ft_strlen(directory) + ft_strlen(prompt) + 2;
	exec_path = malloc(total_length);
	if (!exec_path)
	{
		free(directory);
		return (NULL);
	}
	ft_strcpy(exec_path, directory);
	ft_strcat(exec_path, "/");
	ft_strcat(exec_path, prompt);
	free(directory);
	return (exec_path);
}

int	my_exec(char *cmd, char **envp)
{
	char	**args;
	char	*directory;
	char	*cmd_path;
	args = ft_split(cmd, ' ');
	if (!args)
		return (-1);
	int i = 0;
	directory = check_all_dirs(args[0]);
	if (!directory)
		return (free_array(args), -1);
	cmd_path = ft_concat_path(directory, args[0]);
	if (!cmd_path)
		return (free(directory), free_array(args), -1);
	if (execve(cmd_path, args, envp) == -1)
		return (perror("execve failed"), free_array(args), free(cmd_path), -1);
	return (0);
}

char	**distribute_cmds(int argc, char **argv)
{
	char	**cmds;
	int		i;
	int		j;

	j = 0;
	i = 1;
	cmds = malloc((argc) * sizeof(char *));
	if (!cmds)
		return (NULL);
	while (i < argc && argv[i] != NULL)
	{
		cmds[j] = ft_strdup(argv[i]);
		if (!cmds[j])
			return (free_array(cmds), NULL);
		j++;
		i++;
	}
	cmds[j] = NULL;
	return (cmds);
}

void	handle_child(int i, int fds[2], int cmd_count, int prev_fd, char **cmds, char **envp)
{
	if (i == 0) //  1st cmd
	{
		int	input_fd = open("file1.txt", O_RDONLY);
		dup2(input_fd, STDIN_FILENO);
	}
	else // (i > 0) //not first cmd.
	{
		dup2(prev_fd, STDIN_FILENO); // --> proteger appel a pid, apres refacto);
		close(prev_fd);
	}
	if (i < cmd_count - 1) // not last cmd.
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	else
	{
		int	output_fd = open("file2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(output_fd, STDOUT_FILENO);
	}
	if (my_exec(cmds[i], envp) == -1)
		free_array(cmds);
	close(fds[0]);
}

void	handle_parent(int i, int fds[2], int prev_fd, int cmd_count)
{
	if (i > 0)
		close(prev_fd);
	if (i < cmd_count - 1)
		close(fds[1]);
}

void	wait_all(int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	pipex(int cmd_count, char **cmds, char **envp)
{
	int		i;
	int		prev_fd;
	int		fds[2];
	pid_t	pid;

	prev_fd = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (pipe(fds) == -1)
			return (perror("pipe failed"), free_array(cmds), -1);
		pid = fork();
		if (pid == -1)
			return (perror("fork failed"), free_array(cmds), -1);
		else if (pid == 0)
			handle_child(i, fds, cmd_count, prev_fd, cmds, envp); // retour d'erreur ?
		else
		{
			handle_parent(i, fds, prev_fd, cmd_count); //retour d'erreur ?
			prev_fd = fds[0];
		}
		i++;
	}
	wait_all(cmd_count);
	return (0);
}

int	pipex_main(t_data *data, int argc, char **argv, char **envp)
{
	int		cmd_count;
	char	**cmds;
	cmd_count = argc - 1;
	
	if (argc < 2)
		return (ft_printf("Usage: ./pipex cmd1 cmd2 ... cmdN\n"), -1);
	cmds = distribute_cmds(argc, argv);
	if (!cmds)
		return (-1);
	if (pipex(cmd_count, cmds, envp) == -1)
		return (-1);
	free_array(cmds);
	return (0);
}

// tests : 
// ./pipex  rev sort "cat -e" "tr 'o' 'x'" 




// ###### PROTO ######



int		exec(t_data *data, int tab_size)
{
	if (!data)
		return (-1);
	print_struct(data, tab_size);
	return (0);
}
