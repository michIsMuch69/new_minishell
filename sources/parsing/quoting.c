/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:07:06 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/06 08:28:27 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

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

// char	*expand_management(char *token, char **envp)
// {
// 	getenv()
// }

// bool	include_expand(char *token) //return the $ sign position
// {
// 	int	i;

// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '$')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// bool	find_occur(char *token, char *env)
// {
// 	size_t	i;

// 	i = 0;
// 	while (env[i] && token[i])
// 	{
// 		if (token[i] && )
// 			return (0);
// 	}
// }

// char	*ft_getenv(char *var_name, char **env)
// {
// 	size_t	i;
// 	char	*tmp;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (find_occur(var_name, env[i]))
// 		{

// 		}
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }

// char	*extract_env(char *token, size_t i, char **env)
// {
// 	char			*tmp;
// 	size_t			var_size;
// 	const size_t	start = ++i;
	
// 	var_size = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == 9 || token[i] == 32 || token[i] == 34)
// 			break;
// 		else	
// 			var_size++;
// 		i++;
// 	}


// 	tmp = ft_calloc(var_size + 1, sizeof(char));
// 	if (!tmp)
// 		return (NULL);
// 	tmp = ft_memcpy(tmp, &(token[start]), var_size);
// 	printf("var name %s\n", tmp);


// 	tmp = ft_getenv(tmp, env);
// 	if (!tmp)
// 		return (NULL);
	
// 	return (tmp);
// }

// char	*change_expand(char *token, char **envp)
// {
// 	size_t	i;
// 	char	*tmp;
	
// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '$')
// 			tmp = extract_env(token, i, envp);
// 		i++;
// 	}
// 	return (NULL);
// }

static char	*double_quote(char *token, char **envp)
{
	char	*tmp;

	if (quoting_count(token, '"'))
		return (ft_perror("error -> syntax\n"), NULL);
	// if (include_expand(token))
	// {
	// 	tmp = change_expand(token, envp);
	// 	return (final_build(tmp, '"'));
	// }
	else
		return (final_build(token, '"'));
}

static char	*simple_quote(char *token)
{
	if (quoting_count(token, '\''))
		return (ft_perror("error -> syntax\n"), NULL);
	return (final_build(token, '\''));
}

char	*quote_management(char *token, char **envp)
{
	if (token[0] == '\'')
		return (simple_quote(token));
	else if (token[0] == '"')
		return (double_quote(token, envp));
	return (NULL);
}
