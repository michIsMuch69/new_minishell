/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/05 14:52:57 by jedusser         ###   ########.fr       */
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

int		exec(t_data *data, int tab_size)
{
	char	*directory1;
	char	*directory2;
	char	*cmd_path1;
	char	*cmd_path2;
	pid_t	pid;
	int		i;

	i = 0;
	if (!data)
		return (-1);
	printf("%d\n", tab_size);
	
	directory1 = check_all_dirs(data[0].args.tab[0]);
	if (!directory1)
		return (-1);
		
	directory2 = check_all_dirs(data[1].args.tab[0]);
	if (!directory2)
		return (-1);
		
	printf("Directory = %s\n", directory1);
	printf("Directory = %s\n", directory2);
	
	cmd_path1 = ft_concat_path(directory1, data[0].args.tab[0]);
	if (!cmd_path1)
		return (-1);
		
	cmd_path2 = ft_concat_path(directory2, data[1].args.tab[0]);
	if (!cmd_path2)
		return (-1);
		
	printf("cmd_path = %s\n", cmd_path1);
	printf("cmd_path = %s\n", cmd_path2);
	
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path1, data[0].args.tab, data[0].env.tab);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}