/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:58:11 by jedusser          #+#    #+#             */
/*   Updated: 2024/07/09 07:30:07 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <struct.h>
#include <libft.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// ###### INCLUDES ######


// ###### PROTO ######

int		ft_perror(char *err_message);
int		init_sighandler(t_data *data);
int		parse_prompt(char **envp, t_data **data);
void	free_struct(t_data *struc, int tab_size);
void	free_tab(t_table *tab, int start);
int		exec(int tab_size, t_data *data);
int     ft_getenv(char *word, char **env, char **var_content);
t_table ft_tabdup(char **envp);

// ###### PROTO ######

/*
	* leak test with valgrind :
	* valgrind --suppressions=run.sh --leak-check=full ./minishell
*/

// function only for tests
void	print_tab(t_table tab)
{
	int	i = 0;

	while(i < tab.size)
		printf("%s\n", tab.tab[i++]);
}

// function only for tests
void	print_struct(t_data *data, int tab_size)
{
	int	i = 0;
	int	y = 0;

	while (i < tab_size)
	{
		printf("\nSTRUC %d\n\n", i+1);
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

static t_data	*reset_env(t_data *data, int tab_size)
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
		return (free_tab(&tmp, 0), ft_perror("error -> reset env\n"), NULL);
	data->env.tab = tmp.tab;
	data->env.size = tmp.size;
	return (data);
}

static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_perror("error -> init structure\n"), NULL);
    if (init_sighandler(data) == -1)
        return (NULL);
	data->env = ft_tabdup(envp);
	if (!data->env.tab)
		return (free(data), ft_perror("error -> init structure\n"), NULL);
	return (data);
}

int main (int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (ft_perror("arguments are invalid\n"), 1);
	data = init_data(envp);
	if (!data)
		return (2);
	while (1)
	{
		data->prompt = readline("\033[32mmini$hell>\033[0m ");
        if (!data->prompt)
            return (free_struct(data, 1), exit(EXIT_SUCCESS), 0);
		add_history(data->prompt); // !! need to clear history
		data->tab_size = parse_prompt(data->env.tab, &data);
		if (data->tab_size == -1)
			return (free_struct(data, 1), 4);
		if (data->tab_size)
            if (exec(data->tab_size, data) == -1)
			    return (free_struct(data, 1), 5);
		data = reset_env(data, data->tab_size);
		if (!data)
			return (5);
	}
	return (0);
}
