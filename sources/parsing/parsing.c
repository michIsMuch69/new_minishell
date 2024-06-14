/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/14 15:11:27 by fberthou         ###   ########.fr       */
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
void	free_tab(t_table tab, int start);

char	*pre_treatment(char *prompt, int i);
t_table	tokenizer(char *prompt);
int		token_cleaner(t_table *tokens, char **envp, t_table *table);
int		expand_management(t_data *data, char **envp);
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
	t_table	tokens; // only for test ?
	int		struc_tab_size;
	int		ret_value;

// ### pre treatment ### //
	*prompt = pre_treatment(*prompt, 0);
	if (!*prompt)
		return (-1);
	printf("p_prompt == %s\n", *prompt);
// ### token initialization ### //

	tokens = tokenizer(*prompt);
	if (!tokens.tab)
		return (free(*prompt), -1); // ! double free

	//print_tab(tokens);

// ### structure initialization ### //
	struc_tab_size = init_struct(data, &tokens, 0, 0);
	if (struc_tab_size == -1)
		return (free_tab(tokens, 0), free(*prompt), -1);
	
	//print_struct(*data, struc_tab_size);

// ### expand variables in token struct  ### //
	ret_value = expand_management(*data, env);
	if (ret_value == -1)
		return (free_tab(tokens, 0), -1);
	if (ret_value == 1)
		return(free_tab(tokens, 0), 0);

	print_struct(*data, struc_tab_size);
// ### expand variables in token struct  ### //


// ### clean tokens to real cmd / args ### //

	// ret_value = token_cleaner(&tokens, env, &args); //0 = ok -1 error_crash, 1 syntaxe
	// if (ret_value == 1)
	// 	return (free_tab(tokens, 0), 0);
	// if (ret_value == -1)
	// 	return (free_tab(tokens, 0), free(*prompt), -1); // free all is temporary, t_table token.tab is free in token_cleaner
	// //print_tab(*args);
	// free_tab(tokens, 0);

// ### clean tokens to real cmd / args END ### //

	return (free_tab(tokens, 0), struc_tab_size);
}
