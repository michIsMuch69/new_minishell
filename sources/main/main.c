// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <readline/readline.h> 
#include <readline/history.h>

// ###### INCLUDES ######


// ###### PROTO ######

size_t	ft_perror(char *err_message);
char	*init_env(void);
int		parse_prompt(char *prompt, char **envp, t_data **data);
void	free_struct(t_data *ptr, size_t tab_size);

// ###### PROTO ######

/*
	* leak test with valgrind :
	* valgrind --suppressions=run.sh --leak-check=full ./minishell
*/

int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	char	*env_name; // optional
	int		struct_tabsize;
	t_data	*data;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	env_name = NULL;
	while (1)
	{
		// env_name = init_env();
		prompt = readline(/*env_name*/">>> ");
		add_history(prompt);
		struct_tabsize = parse_prompt(prompt, envp, &data);
		if (struct_tabsize == -1)
			return (/*free(env_name)*/free(prompt), 2);
		//exec(data, tab_size);
		free(prompt);
		
		free_struct(&data, struct_tabsize);
	}
	return (0);
}
