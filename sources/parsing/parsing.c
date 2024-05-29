/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/29 17:19:29 by fberthou         ###   ########.fr       */
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
void	free_all(t_table tab, t_data *ptr, size_t tab_size);

t_table	tokenizer(char *prompt);
t_table	*token_cleaner(t_table tokens, char **envp);


int	fill_struct(t_data **struc_tab, t_table *tokens, char **envp);

// ###### PROTOTYPES ######


// function only for tests
void	print_tab(char **table)
{
	size_t	i = 0;

	while(table[i])
		printf("%s\n", table[i++]);
}

// function only for tests
void	print_struct(t_data *data, size_t tab_size)
{
	size_t	i = 0;
	size_t	y = 0;
	
	while (i < tab_size)
	{
		printf("type = %d\n", data[i].cmd_type);
		printf("cmd = %s\n", data[i].cmd);
		if (data[i].opt)
			while (data[i].opt[y])
				printf("opt = %s\n", data[i].opt[y++]);
		y = 0;
		if (data[i].args)
			while (data[i].args[y])
				printf("arg = %s\n", data[i].args[y++]);
		y = 0;
		i++;
	}
}



/*
	* parse_prompt ft -> have to return an int ? YES !
*/

int	parse_prompt(char *prompt, char **envp, t_data **data)
{
	t_table	*tok;
	int		i_struc;

// ### token initialization ### //
	t_table	token; // only for test

	token = tokenizer(prompt);
	if (!token.size && !token.tab)
		return (-1);

	// print tab only for test //
	//print_tab(token.tab);

// ### token initialization END ### //



// ### clean tokens to real cmd ### //

	tok = token_cleaner(token, envp);
	if (!tok)
		return (free_all(token, NULL, 0), -1); // free all is temporary, t_table token.tab is free in token_cleaner

	// print tab only for test //
	print_tab(tok->tab);

// ### clean tokens to real cmd END ### //



// ### structure initialization ### //

	i_struc = fill_struct(data, tok, envp);
	if (i_struc == -1)
	{
		free_all(*tok, NULL, 0);
		free(tok);
		free_all(token, NULL, 0);
		return (-1);
	}
	i_struc++;

	// print struct only for test //
	// print_struct(main_s, *i);
// ### structure initialization END ### //


	free_all(*tok, NULL, 0);
	free(tok);
	return (free_all(token, NULL, 0), i_struc);
}
