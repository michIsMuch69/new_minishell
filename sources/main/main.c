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


void echo(char *arguments);
int	exec_found(const char *dirname, char *exec_searched);
char	*check_all_dirs(char **envp, char *exec_searched);

int main (int argc, char **argv, char **envp)
{

	char	*arguments = "ceci peut etre $PATH ecrit apres echo";
	char	*exec_searched = "ls";
	char 	*prompt;
	char	*env;
	t_cmd	*lst;
	pid_t 	pid;
	int 	i;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"));
	while (1)
	{
		//printf("%d\n", getpid());
		env = get_pwd();
		prompt = readline(env);
		add_history(prompt);
		//printf("%s\n", prompt);
		echo(arguments);
		//printf("%d\n", exec_found("/bin"));
		printf("%s\n", check_all_dirs(envp, exec_searched));
		execve(check_all_dirs(envp, exec_searched), argv, envp);
		//echo(prompt);
		//lst = parse_prompt(prompt);
		//exec(lst);
		free(env);
	}
	return (0);
}