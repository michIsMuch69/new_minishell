// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <stdio.h>
#include <readline/readline.h> 
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

// ###### INCLUDES ######


// ###### PROTO ######

char	*get_pwd(void);
size_t	ft_perror(char *err_message);
t_cmd	*parse_prompt(char *prompt);

// ###### PROTO ######



int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	char	*env;
	t_cmd	*lst;
	pid_t 	pid;
	int 	i;
	if (argc != 1)
		return (ft_perror("arguments are invalid\n"));
	printf("coucou\n");
	pid = fork();
	if(pid == 0)
		execve("/bin/ls", argv, envp);
	else
		waitpid(pid, &i, 0);
	if(pid != 0)
	{
		while (1)
		{
			printf("%d\n", getpid());
			env = get_pwd();
			prompt = readline(env);
			add_history(prompt);
			printf("%s\n", prompt);
			//lst = parse_prompt(prompt);
			//exec(lst);
			free(env);
		}

	}
	return (0);
}