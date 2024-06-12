/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:27:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/12 14:37:05 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "struct.h"
#include "libft.h"
#include "stdbool.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

int		ft_getenv(char *word, char **env, char **var_content);
char	*extract_word(char *str, int start, int end);

// ###### PROTOTYPES ######

int	find_size(char *str, int start, int end)
{
	int	i;

	i = 0;
	// printf("start = %d, end = %d\n", start, end);
	while (str[i] && i < start)
		i++;
	while (str[end++])
		i++;
	//printf("find_size of $var = %d\n", i);
	return (i);
}

int	cut_str(char **token, int start, int end)
{
	char	*tmp;
	int		i;

	i = 0;
	// printf("cutstr : start = %d, end = %d\n", start, end);
	tmp = ft_calloc(find_size(*token, start, end) + 1, sizeof(char));
	if (!tmp)
		return (ft_perror("error -> alloc cut_str\n") -1);
	while (i < start)
	{
		tmp[i] = token[0][i];
		i++;
	}
	while (token[0][end])
	{
		tmp[i] = token[0][end];
		end++;
		i++;
	}
	free(token[0]);
	token[0] = tmp;
	printf("cut str token = %s\n", tmp);
	return (0);
}

char	*init_join_str(size_t size, size_t *i_str, size_t *i_tok)
{
	char	*tmp;

	*i_str = 0;
	*i_tok = 0;
	if (size > 0)
	{
		tmp = ft_calloc(size, sizeof(char));
		if (!tmp)
			return (ft_perror("error-> alloc join_str\n"), NULL);
	}
	else
		return (NULL);
	return (tmp);
}

int	join_str(char **token, int start, int end, char *var_content)
{
	char	*str;
	size_t	i_str;
	size_t	i_tok;

	str = init_join_str((ft_strlen(*token) - (end - start) + \
		ft_strlen(var_content) + 1), &i_str, &i_tok);
	if (!str)
		return (-1);
	while(i_str < start)
	{
		str[i_str] = token[0][i_str];
		i_str++;
	}
	while (var_content[i_tok])
	{
		str[i_str] = var_content[i_tok++];
		i_str++;
	}
	while (token[0][end])
	{
		str[i_str] = token[0][end++];
		i_str++;
	}
	return (free(*token), free(var_content), *token = str, 0);
}

int	extract_var(char **token, char **env, int start, int end)
{
	// extract the word after the $ sign and copy it in a tmp buffer
	// find if this var exist in envp
		// if word is not in envp cut the $+world
		// if yes, copy the value of the var in a buffer
	char	*word;
	char	*var_content;
	int		ret_value;

	word = extract_word((*token), start + 1, end);
	if (!word)
		return (-1); //malloc error
	ret_value = ft_getenv(word, env, &var_content);
	if (ret_value == 1) // no varriable
		return (free(word), cut_str(token, start, end)); //cut_str
	else if (ret_value == -1)
		return (free(word), -1); //malloc error
	free(word);
	return (join_str(token, start, end, var_content)); // join var_content to the token
}

int	expand_management(char **token, char **envp, char c)
{
	int	i;
	int	start;

	i = 0;
	while (token[0][i])
	{
		if (c == '"' && token[0][i] == '$')
		{
			start = i++;
			if (token[0][i] >= 48 && token[0][i] <= 57)
			{
				if (cut_str(token, start, (i + 1)) == -1) // ignore the $7 and keep the rest of the string
					return (-1);
			}
			else if (token[0][i] == 9 || token[0][i] == 32)
				return (0);
			else
			{
				while (token[0][i] && token[0][i] != 9 && \
					token[0][i] != 32 && token[0][i] != '|' && \
					token[0][i] != '$' && token[0][i] != c)
					i++;
				if (extract_var(token, envp, start, i) == -1) // change the value or cut it if not in envp
					return (-1);
			}
			i = -1;
			printf("token = %s\n", token[0]);
		}
		else if (!c && token[0][i] == '$')
		{
			start = i++;
			if (token[0][i] >= 48 && token[0][i] <= 57)
			{
				if (cut_str(token, start, (i + 1)) == -1) // ignore the $7 and keep the rest of the string
					return (-1);
			}
			else if ((token[0][i] < 65 || token[0][i] > 90) && \
					(token[0][i] < 97 || token[0][i] > 122))
			{
				if (cut_str(token, start, (i + 1)) == -1) // ignore the $7 and keep the rest of the string
					return (-1);
			}
			else
			{
				while (token[0][i] && token[0][i] != 9 && \
					token[0][i] != 32 && token[0][i] != '|' && \
					token[0][i] != '$')
					i++;
				if (extract_var(token, envp, start, i) == -1) // change the value or cut it if not in envp
					return (-1);
			}
			i = -1;
			printf("token = %s\n", token[0]);
		}
		i++;
	}
	return (0);
}

