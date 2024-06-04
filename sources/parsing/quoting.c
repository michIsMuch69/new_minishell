/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:07:06 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 13:41:06 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <stdbool.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

int		include_expand(char *token);
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

// static char	*double_quote(char *token, char **envp)
// {
// 	int i;

// 	if (quoting_count(token, '"'))
// 		return (NULL);
// 	i = include_expand(token);
// 	if (i >= 0)
// 		return (expand_management(token, '"', envp));
// 	else
// 		return (final_build(token, '"'));
// }

static char	*simple_quote(char *token)
{
	if (quoting_count(token, '\''))
		return (ft_perror("error -> syntax\n"), NULL);
	return (final_build(token, '\''));
}

char	*quote_management(char *token, char **envp)
{
	char	*data = NULL;

	if (token[0] == '\'')
		data = simple_quote(token);
	// else if (token[0] == '"')
	// 	data = double_quote(token, envp);

	return (data);
}
