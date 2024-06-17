/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/12 14:55:29 by jedusser         ###   ########.fr       */
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

char	*pre_treatment(char *prompt);
t_table	tokenizer(char *prompt);
int		token_cleaner(t_table *tokens, char **envp, t_table *table);
int		init_struct(t_data **data, t_table *tokens, size_t start, size_t data_size);

void	print_tab(t_table tab);
void	print_struct(t_data *data, int tab_size);


// ###### PROTOTYPES ######

/*
	* parse_prompt ft -> have to return an int ? YES !
*/


int	parse_prompt(char **prompt, char **env, t_data **data)
{
	t_table	args;
	int		struc_tab_size;
	int		ret_value;

// ### pre treatment ### //

	*prompt = pre_treatment(*prompt);
	if (!*prompt)
		return (-1);
	
	//printf("p_prompt == %s\n", *prompt);

// ### pre treatment ### //


// ### token initialization ### //
	t_table	token; // only for test

	token = tokenizer(*prompt);
	if (!token.tab)
		return (free(*prompt), -1); // ! double free

	//print_tab(token);

// ### token initialization END ### //

	//printf("<- tokens\n\nclean tokens ->\n");

// ### clean tokens to real cmd / args ### //

	ret_value = token_cleaner(&token, env, &args); //0 = ok -1 error_crash, 1 syntaxe
	if (ret_value == 1)
		return (free_tab(token), 0);
	if (ret_value == -1)
		return (free_tab(token), free(*prompt), -1); // free all is temporary, t_table token.tab is free in token_cleaner
	//print_tab(*args);
	free_tab(token);

// ### clean tokens to real cmd / args END ### //


// ### structure initialization ### //

	struc_tab_size = init_struct(data, &args, 0, 0);
	if (struc_tab_size == -1)
		return (free_tab(args), free(*prompt), -1);

	// print struct only for test //
	// printf("struc_tab_size = %d\n", struc_tab_size);
	print_struct(*data, struc_tab_size);
	
// ### structure initialization END ### //

	return (free_tab(args), struc_tab_size);
}
