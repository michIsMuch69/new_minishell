/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:26:45 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/11 11:09:37 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "struct.h"
#include "libft.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);
void	free_tab(t_table tab);

int		quote_management(t_table *token, int i_token, char **envp, t_table *args);
int		expand_management(char **token, char **envp, char c);

// ###### PROTOTYPES ######


static int	clean_token(t_table *token, int i_tok, char **envp, t_table *args)
{
	int	ret_value;

	if (token->tab[i_tok][0] == '\'' || token->tab[i_tok][0] == '"')
		return (quote_management(token, i_tok, envp, args));
	else
	{
		args->tab[args->size] = ft_strdup(token->tab[i_tok]);
		if (!args->tab[args->size])
			return (-1);
	}
	return (0);
}

int	token_cleaner(t_table *tokens, char **env, t_table *args)
{
	int	ret_value;

	if (!tokens->tab)
		return (-1);
	args->tab = ft_calloc(sizeof(char *), tokens->size + 1);
	if (!args->tab)
		return (ft_perror("error-> cleaner tab alloc\n"), -1);
	args->size = 0;
	while (args->size < tokens->size)
	{
		ret_value = clean_token(tokens, args->size, env, args);
		if (ret_value == -1)
			return (free_tab(*args), -1);
		if (ret_value == 1)
			return (free_tab(*args), 1);
		(args->size)++;
	}
	return (0);
}
