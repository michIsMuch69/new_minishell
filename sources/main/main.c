#include "libft.h"
#include <errno.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

#include <dirent.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>

#include <readline/readline.h> 
#include <readline/history.h>

#include "struct.h"

size_t	ft_perror(char *err_message)
{
	return(write(2, err_message, ft_strlen(err_message)));
}

int main (int argc, char **argv, char **envp)
{
	int			 	i = 0;
	pid_t			pid;
	DIR				*dir;
	struct dirent	*ry;
	char 			*buffer;
	char			*env;
	t_cmd			*cmd;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"));
	
	while (1)
	{
		env = ft_strdup(getenv("PWD"));
		env = ft_realloc(env, (ft_strlen(env) + 3), ft_strlen(env));
		i = ft_strlen(env);
		env[i] = '$';
		i++;
		env[i] = ' ';
		buffer = readline(env);
		add_history(buffer);
		printf("%s\n", buffer);
		free(env);
	}

	//pid = fork();
	// if (pid == 0)
	// {
		// val = execve("/usr/bin/ls", argv, envp);
		// if (val == -1)
		// 	return (printf("%s\n", strerror(errno)), 0);
	// }
	// if (pid > 0)
	// 	waitpid(pid, &i, 0);
	// dir = opendir("./");
	// ry = readdir(dir);
	// while (ry)
	// {
	// 	printf("file type : '%c', filename : '%s'\n", ry->d_type, ry->d_name);
	// 	ry = readdir(dir);
	// }
	// if (closedir(dir))
	// 	perror(NULL);
	return (0);
	
}