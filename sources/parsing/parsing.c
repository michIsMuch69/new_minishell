/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/31 17:29:04 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "struct.h"
#include "libft.h"
#include "parsing.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	free_tab(char **tab, int tab_size);
void	free_struct(t_data *struc, size_t tab_size);

t_table	tokenizer(char *prompt);
t_table	*token_cleaner(t_table tokens, char **envp);

int	set_table(t_data **data, t_table *tokens, size_t start, size_t data_size);

// ###### PROTOTYPES ######


// function only for tests
void	print_tab(t_table tab)
{
	size_t	i = 0;

	printf("tab_size : %d\n", tab.size);
	while(i <= tab.size)
		printf("%s\n", tab.tab[i++]);
}

// function only for tests
// void	print_struct(t_data *data, size_t tab_size)
// {
// 	size_t	i = 0;
// 	size_t	y = 0;
	
// 	while (i < tab_size)
// 	{
// 		printf("type = %d\n\n", (int) data[i].cmd_type);
// 		printf("cmd  = %s\n\n", data[i].cmd);
// 		y = 0;
// 		if (data[i].args.tab[y])
// 			while (y < data[i].args.size)
// 				printf("arg  = %s\n", data[i].args.tab[y++]);
// 		printf("\n");
// 		y = 0;
// 		if (data[i].env)
// 			while (data[i].env[y])
// 				printf("arg  = %s\n", data[i].env[y++]);
// 		i++;
// 	}
// }

/*
	* parse_prompt ft -> have to return an int ? YES !
*/

int	parse_prompt(char *prompt, char **env, t_data **data)
{
	t_table	*args;
	int		struc_tab_size;

// ### token initialization ### //
	t_table	token; // only for test

	token = tokenizer(prompt);
	if (!token.tab)
		return (-1);

	// print tab only for test //
	print_tab(token);

// ### token initialization END ### //

	printf("<- tokens\n\nclean tokens ->\n");

// ### clean tokens to real cmd ### //

	args = token_cleaner(token, env);
	if (!args)
		return (free_tab(token.tab, token.size), -1); // free all is temporary, t_table token.tab is free in token_cleaner

	// print tab only for test //
	print_tab(*args);
	free_tab(token.tab, token.size);

// ### clean tokens to real cmd END ### //



// ### structure initialization ### //

	struc_tab_size = set_table(data, args, 0, 0);
	if (struc_tab_size == -1)
		return (free_tab(args->tab, args->size), free(args), -1);

	// print struct only for test //
	printf("struc_tab_size = %d\n", struc_tab_size);
	// print_struct(main_s, *i);
	
// ### structure initialization END ### //


	free_tab(args->tab, args->size);
	free(args);

	return (struc_tab_size);
}
