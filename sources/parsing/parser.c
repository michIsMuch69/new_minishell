/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:26:45 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/29 17:21:31 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "struct.h"
#include "libft.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

void	free_all(t_table tab, t_data *ptr, size_t tab_size);
char	*quote_management(char *token, char **envp);
size_t	ft_perror(char *err_message);

// ###### PROTOTYPES ######


static char	*clean_token(char *token, char **envp)
{
	char	*arg;
	size_t	i;

	i = 0;
	if (token[i] == '\'' || token[i] == '"')
		return (quote_management(token, envp));
	// else if (token[i] == '$')
	// 	arg = expand_management(token, envp);
	else
		return (ft_strdup(token));
}

t_table	*token_cleaner(t_table tokens, char **envp)
{
	char	**args;
	t_table	*table;

	if (!tokens.size && !tokens.tab)
		return (NULL);
	table = ft_calloc(sizeof(t_table), 1);
	if (!table)
		return (ft_perror("error -> cleaner struct mem alloc\n"), NULL);
	//printf("token tab size : %zu\n", tokens.size);
	table->tab = ft_calloc(sizeof(char *), tokens.size + 1);
	if (!table->tab)
		return (free(table), ft_perror("error -> cleaner S_tab mem alloc\n"), NULL);
	table->size = 0;
	while (table->size < tokens.size)
	{
		table->tab[table->size] = clean_token(tokens.tab[table->size], envp);
		if (!table->tab[table->size])
			return (free_all(*table, NULL, 0), free(table), NULL);
		(table->size)++;
	}
	return (/*free_all(tokens, NULL, 0),*/ table); // free tokens in parse_prompt ft during builting ans test
}
