/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:42:33 by jedusser          #+#    #+#             */
/*   Updated: 2024/05/23 16:23:25 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}

int	exec_found(const char *dirname, char *exec_searched)
{
	DIR				*dir;
	struct dirent	*entity;
	
	dir = opendir(dirname);
	if(!dir)
		return (-1);
	entity = readdir(dir);
	while (entity != NULL)
	{
		if(ft_strcmp(entity->d_name, exec_searched) == 0)
			return(1);
		entity = readdir(dir);
	}
	closedir(dir);
	return (0);
}

//function our change de dir.
char	*check_all_dirs(char **envp, char *exec_searched)
{
	const char	*paths = getenv("PATH");
	char		**path_list;
	path_list = ft_split(paths, ':');
	if(!path_list)
		return (NULL);
	int i = 0;
	while (path_list[i])
	{
		if(exec_found(path_list[i], exec_searched) == 1)
			return(path_list[i]);
		i++;
	}
	return (NULL);
}


// check absolutely if file is an executable (entity->d_type)//
// an if rights are OK