/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:10:11 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/14 16:31:49 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include "libft.h"

#include <stdio.h>

// ###### INCLUDES ######


// ###### PROTOTYPES ######

// main/utils.c
size_t	ft_perror(char *err_message);

// parsing/getenv.c
int		ft_getenv(char *word, char **env, char **var_content);

// parsing/parsing_utils.c
int		include_char(char *token, char c, int start);

// parsing/parsing_utils_nd
int		join_str(char **token, int start, int end, char *var_content);

// ###### PROTOTYPES ######

static int	find_end(char *str, int start)
{
	while (str[start] && str[start] != '"' && str[start] != '\'' && \
		str[start] != '<' && str[start] != '>' && str[start] != '$' && \
		str[start] != 9 && str[start] != 32)
		start++;
	return (start);
}

char	*extract_word(char *str, int start)
{
	char	*tmp;
	int		end;
	int		i;

	i = 0;
	end = find_end(str, start + 1);
	tmp = ft_calloc((end - start) + 1, sizeof(char));
	if (!tmp)
		return (ft_perror("error-> alloc extract word\n"), NULL);
	while (start < end)
	{
		tmp[i] = str[start];
		i++;
		start++;
	}
	return (tmp);
}

int	change_value(char **token, char **envp)
{
	int		i;
	int		tmp;
	char	*word;
	char	*var_content;

	i = include_char(token[0], '$', 0) + 1;
	if (!i)
		return (0);
	word = extract_word(token[0], i);
	if (!word)
		return (-1);
	tmp = ft_getenv(word, envp, &var_content);
	if (tmp == 1) // no varriable
		return (free(word), 1);
	else if (tmp == -1)
		return (free(word), -1); //malloc error
	free(word);
	return (join_str(token, i - 1, ft_strlen(*token), var_content)); // join var_content to the token	
}

int	find_size(char *str, int start, int end)
{
	int	i;

	i = 0;
	while (str[i] && i < start)
		i++;
	while (str[end++])
		i++;
	return (i);
}

int	cut_str(char **token, int start, int end)
{
	char	*tmp;
	int		i;

	i = -1;
	start = include_char(token[0], '$', 0);
	if (start == -1)
		return (0);
	end = find_end(token[0], start);
	tmp = ft_calloc((ft_strlen(token[0]) - (end - start) + 1), sizeof(char));
	if (!tmp)
		return (ft_perror("error-> alloc cut_str\n"), -1);
	while (++i < start)
		tmp[i] = token[0][i];
	while (token[0][end])
	{
		tmp[i] = token[0][end];
		i++;
		end++;
	}
	free(token[0]);
	token[0] = tmp;
	return (0);	
}

int	count_sign(char *str, char sign)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == sign)
		i++;
	return (i);
}

