/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 11:31:55 by fberthou         ###   ########.fr       */
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
void	free_tab(t_table tab);
void	free_struct(t_data *struc, size_t tab_size);

t_table	tokenizer(char *prompt);
t_table	*token_cleaner(t_table tokens, char **envp);
int	init_table(t_data **data, t_table *tokens, size_t start, size_t data_size);

void	print_tab(t_table tab);
void	print_struct(t_data *data, int tab_size);


// ###### PROTOTYPES ######

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
	// print_tab(token);

// ### token initialization END ### //

	// printf("<- tokens\n\nclean tokens ->\n");

// ### clean tokens to real cmd / args ### //

	args = token_cleaner(token, env);
	if (!args)
		return (free_tab(token), -1); // free all is temporary, t_table token.tab is free in token_cleaner

	// print tab only for test //
	// print_tab(*args);
	free_tab(token);

// ### clean tokens to real cmd / args END ### //



// ### structure initialization ### //

	struc_tab_size = init_table(data, args, 0, 0);
	if (struc_tab_size == -1)
		return (free_tab(*args), free(args), -1);

	// print struct only for test //
	// printf("struc_tab_size = %d\n", struc_tab_size);
	// print_struct(main_s, *i);
	
// ### structure initialization END ### //

	return (free(args->tab), free(args), struc_tab_size);
}
