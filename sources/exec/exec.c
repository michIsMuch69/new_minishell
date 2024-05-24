/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:42:33 by jedusser          #+#    #+#             */
/*   Updated: 2024/05/24 10:51:00 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

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
// this function checks if exec is found within a directory.

int	exec_found(const char *dirname, char *exec_searched)
{
	DIR				*dir;
	struct dirent	*entity;

	dir = opendir(dirname);
	if (!dir)
	{
		//perror("Failed to open directory");
		return (-1);
	}
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

// this function checks if exec is found in all concerned directories 
// and returns the directory where it has been found.

char	*check_all_dirs(char **envp, char *exec_searched)
{
	const char	*paths = getenv("PATH");
	char		**path_list;
	int			i;

	path_list = ft_split(paths, ':');
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		if (exec_found(path_list[i], exec_searched) == 1)
		{
			return (path_list[i]);
			break ;
		}
		i++;
	}
	free_array(path_list);
	return (NULL);
}

//TO_DO : 
// -check absolutely if file is an executable (entity->d_type)//
// an if rights are OK