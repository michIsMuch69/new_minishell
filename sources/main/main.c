// ###### INCLUDES ######

#include "libft.h"
#include "struct.h"
#include <readline/readline.h> 
#include <readline/history.h>

// ###### INCLUDES ######


// ###### PROTO ######

size_t	ft_perror(char *err_message);
int		parse_prompt(char *prompt, char **envp, t_data **data);
void	free_struct(t_data *struc, size_t tab_size);
void	free_tab(char **tab, int tab_size);

void	print_tab(t_table tab);

// ###### PROTO ######

/*
	* leak test with valgrind :
	* valgrind --suppressions=run.sh --leak-check=full ./minishell
*/

t_table	ft_tabdup(char **envp)
{
	t_table	tab_env;
	size_t	i;

	i = 0;
	if (!envp)
		return (tab_env.tab = NULL, tab_env);
	while (envp[i++])
		;
	tab_env.tab = ft_calloc(i + 1	, sizeof(char *));
	if (!tab_env.tab)
		return (tab_env);
	i = 0;
	while (envp[i])
	{
		tab_env.tab[i] = ft_strdup(envp[i]);
		if (!tab_env.tab[i])
			return (free_tab(tab_env.tab, i), tab_env);
		i++;
	}
	tab_env.size = i;
	return (tab_env);
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = ft_tabdup(envp);
	if (!data->env.tab)
		return (free(data), NULL);
	return (data);
}

int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	int		tab_size;
	t_data	*data;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	//print_tab(data->env);
	while (1)
	{
		data = init_data(envp);
		if (!data)
			return (ft_perror("error -> init structure\n"), 2);
		prompt = readline("mini$hell> ");
		add_history(prompt);
		tab_size = parse_prompt(prompt, envp, &data);
		if (tab_size == -1)
			return (free(prompt), 3);
		//exec(data, tab_size);
		free(prompt);

		free_struct(data, tab_size);
	}
	return (0);
}
