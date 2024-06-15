/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:07:06 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/15 15:55:24 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "struct.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

int		expand_management(t_table *token, int i_tok, char **envp, char c);
char	*final_build(char *token, char c);


// ###### PROTOTYPES ######

static bool	quoting_count(char *token, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] == c)
			count++;
		i++;
	}
	if (count % 2)
		return (1);
	return (0);
}

static int	double_quote(t_table *token, int i_tok, char **envp, t_table *args)
{
	if (quoting_count(token->tab[i_tok], '"'))
		return (ft_perror("error -> syntax\n"), 1);
	args->tab[args->size] = final_build(token->tab[i_tok], '"');
	if (!args->tab[args->size])
		return (ft_perror("error-> alloc db quotes\n"), -1);
	return (0);
}

static int	simple_quote(char *token, t_table *args)
{
	int	tmp;

	if (quoting_count(token, '\''))
		return (ft_perror("error -> syntax\n"), 1);
	args->tab[args->size] = final_build(token, '\'');
	if (!args->tab[args->size])
		return (ft_perror("error-> alloc simple quotes\n"), -1);
	return (0);
}

int	quote_management(t_table *token, int i_token, char **envp, t_table *args)
{
	if (token->tab[i_token][0] == '\'')
		return (simple_quote(token->tab[i_token], args));
	else if (token->tab[i_token][0] == '"')
		return (double_quote(token, i_token, envp, args));
	return (0);
}
