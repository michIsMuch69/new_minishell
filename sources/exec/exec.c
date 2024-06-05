/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/05 16:00:33 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"
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
int		exec(int i, t_data *data, int tab_size);
void	free_tab(t_table tab);



// ###### PROTO ######

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
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
int	handle_child(int i, int fds[2], int tab_size, int prev_fd, t_data *data)
{
	// if (i == 0) //  1st cmd
	// {
	// 	int	input_fd = open("file1.txt", O_RDONLY);
	// 	dup2(input_fd, STDIN_FILENO);
	// }
	/*else*/ if (i > 0) //not first cmd.
	{
		dup2(prev_fd, STDIN_FILENO); // --> proteger appel a pid, apres refacto);
		close(prev_fd);
	}
	if (i < tab_size - 1) // not last cmd.
	{
		dup2(fds[1], STDOUT_FILENO);
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
	if (i < tab_size - 1)
		close(fds[1]);
}

void	wait_all(int tab_size)
{
	int	i;

	i = 0;
	while (i < tab_size)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
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
			if(handle_child(i, fds, tab_size, prev_fd, data))
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
char	*ft_concat_path(char *directory, char *prompt)
{
	size_t	total_length;
	char	*exec_path;

	total_length = ft_strlen(directory) + ft_strlen(prompt) + 2;
	exec_path = malloc(total_length);
	if (!exec_path)
	{
		perror("Memory allocation failed for exec_path");
		free(directory);
		return (NULL);
	}
	ft_strcpy(exec_path, directory);
	ft_strcat(exec_path, "/");
	ft_strcat(exec_path, prompt);
	free(directory);
	return (exec_path);
}

int		exec(int i, t_data *data, int tab_size)
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