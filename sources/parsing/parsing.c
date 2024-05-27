/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 07:33:24 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/27 09:32:18 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <struct.h>

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

char	**tokenizer(char *prompt);
void	free_tab(char **tab, size_t tab_size);
size_t	ft_perror(char *err_message);

// ###### PROTOTYPES ######


// function only for tests
size_t	print_tab(char **tok_tab)
{
	size_t	i = 0;

	while(tok_tab[i])
		printf("%s\n", tok_tab[i++]);
	return (i);
}


t_data	*parse_prompt(char *prompt)
{
	char	**tok_tab;
	t_data	*main_struct;
	

	main_struct = malloc(sizeof(t_data));
	if (!main_struct)
		return (ft_perror("error -> main_struct memory allocation\n"), NULL);
	tok_tab = tokenizer(prompt);
	if (!tok_tab)
		return (ft_perror("error -> token extraction\n"), free(main_struct), NULL);
	
	free_tab(tok_tab, (print_tab(tok_tab) + 1));
	return (main_struct);
}