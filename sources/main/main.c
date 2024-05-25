// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <stdio.h>
#include <readline/readline.h> 
#include <readline/history.h>

// ###### INCLUDES ######


// ###### PROTO ######

char	*get_pwd(void);
size_t	ft_perror(char *err_message);
char	**parse_prompt(char *prompt, size_t *tab_size);
void	free_tab(char **tab, size_t tab_size);

// ###### PROTO ######


int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	char	*env;
	char	**tok_tab;
	size_t	tab_size;

	int		i;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	while (1)
	{
		// env = get_pwd();
		prompt = readline(/*env*/">>> ");
		add_history(prompt);
		tok_tab = parse_prompt(prompt, &tab_size);
		if (!tok_tab)
			return (/*free(env),*/ 2);
		i = 0;
		while(tok_tab[i])
			printf("%s\n", tok_tab[i++]);
		free_tab(tok_tab, tab_size);
		//exec(lst);
	}
	return (0);
}
