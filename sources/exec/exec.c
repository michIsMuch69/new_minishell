/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:07:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 16:10:07 by jedusser         ###   ########.fr       */
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
	char	*cmd_path;
	char	*directory;

	if (!data)
		return (-1);
	directory = check_all_dirs(data[0].args.tab[0]);
	//print_tab(data->args);
	cmd_path = ft_concat_path(directory, data[0].args.tab[0]);
	
	printf("cmd_path = %s\n", cmd_path);
	print_struct(data, tab_size);
	execve(cmd_path, data[0].args.tab, data[0].env.tab);
	return (0);
}

