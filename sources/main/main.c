// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <readline/readline.h> 
#include <readline/history.h>

// ###### INCLUDES ######


// ###### PROTO ######

size_t	ft_perror(char *err_message);
char	*init_env(void);
t_data	*parse_prompt(char *prompt);

// ###### PROTO ######

/*
	* leak test with valgrind :
	* valgrind --suppressions=run.sh --leak-check=full ./minishell
*/

int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	char	*env;
	t_data	*args;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	env = NULL;
	while (1)
	{
		// env = init_env();
		prompt = readline(/*env*/">>> ");
		add_history(prompt);
		args = parse_prompt(prompt);
		if (!args)
			return (/*free(env),*/ 2);
		//exec(args);
		free(prompt);
		free(args);
	}
	return (0);
}
