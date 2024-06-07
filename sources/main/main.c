// ###### INCLUDES ######

#include "exec.h"

// ###### INCLUDES ######


// ###### PROTO ######

size_t	ft_perror(char *err_message);
int		parse_prompt(char **prompt, char **envp, t_data **data);
void	free_struct(t_data *struc, size_t tab_size);
void	free_tab(t_table tab);


int		pipex(int tab_size, t_data *data);

void	print_tab(t_table tab);

// ###### PROTO ######

/*
	* leak test with valgrind :
	* valgrind --suppressions=run.sh --leak-check=full ./minishell
*/

// function only for tests
void	print_tab(t_table tab)
{
	size_t	i = 0;

	while(i < tab.size)
		printf("%s\n", tab.tab[i++]);
}

// function only for tests
void	print_struct(t_data *data, int tab_size)
{
	size_t	i = 0;
	size_t	y = 0;
	
	while (i < tab_size)
	{
		printf("\nSTRUC %zu\n\n", i+1);
		printf("cmd  = %s\n", data[i].cmd_path);
		y = 0;
		if (data[i].args.tab)
		{
			printf("args list :\n");
			print_tab(data[i].args);
		}
		if (data[i].input.tab)
		{
			printf("\n");
			printf("inputs :\n");
			print_tab(data[i].input);
		}
		if (data[i].output.tab)
		{
			printf("\n");
			printf("output :\n");
			print_tab(data[i].output);
		}
		printf("\n");
		// y = 0;
		// if (data[i].env.tab)
		// 	print_tab(data[i].env);
		i++;
	}
}

static t_table	ft_tabdup(char **envp)
{
	t_table	tab_env;

	tab_env.size = 0;
	if (!envp)
		return (tab_env.tab = NULL, tab_env);
	while (envp[(tab_env.size)++])
		;
	tab_env.tab = ft_calloc(tab_env.size + 1, sizeof(char *));
	if (!tab_env.tab)
		return (tab_env);
	tab_env.size = 0;
	while (envp[tab_env.size])
	{
		tab_env.tab[tab_env.size] = ft_strdup(envp[tab_env.size]);
		if (!tab_env.tab[tab_env.size])
			return (free_tab(tab_env), tab_env.tab = NULL, tab_env);
		(tab_env.size)++;
	}
	return (tab_env);
}

static t_data	*init_data(char **envp)
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

static t_data	*reset_env(t_data *data, size_t tab_size)
{
	t_table	tmp;

	tmp = ft_tabdup(data->env.tab);
	if (!tmp.tab)
	{
		free_struct(data, tab_size);
		return (ft_perror("error -> reset env\n"), NULL);
	}
	free_struct(data, tab_size);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (free_tab(tmp), ft_perror("error -> reset env\n"), NULL);
	data->env.tab = tmp.tab;
	data->env.size = tmp.size;
	return (data);
}

int main (int argc, char **argv, char **envp)
{
	char 	*prompt;
	int		tab_size;
	t_data	*data;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	data = init_data(envp);
	if (!data)
		return (ft_perror("error -> init structure\n"), 2);
	while (1)
	{
		prompt = readline("mini$hell> ");
		add_history(prompt);
		tab_size = parse_prompt(&prompt, data->env.tab, &data);
		if (tab_size == -1)
			return (free_struct(data, 1), free(prompt), 3);
		// exec(data, tab_size);
		free(prompt);
		data = reset_env(data, tab_size);
		if (!data)
			return (4);
	}
	return (0);
}
