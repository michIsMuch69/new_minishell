/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:27:19 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/13 17:48:42 by fberthou         ###   ########.fr       */
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
int		include_char(char *token, char c, int start);

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
	//printf("cut str token = %s\n", tmp);
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

// int	token_treatment(char **token, char **envp)
// {

// }

int	outfile_management(t_table outfile)
{

}

int	infile_management(t_table infile, char **envp)
{
	int	i_file;

	i_file = 0;
	while (i_file < infile.size)
	{
		if (include_char(infile.tab[i_file], '$', 0) != -1)
			return (ft_perror("ambiguous redirect"), -1);
	}
}

int	expand_management(t_data *data, char **envp)
{
	/*
		* args->tab -> simple_quotes / double quotes
		
		* inputs :
			// if HEREDOC -> keep the litteral value
			// if $NAME is not in env -> ambiguous redirect
			// if $NAME is in env -> change the value
		
		* output :
			// if $NAME is not in env -> ambiguous redirect
			// if $NAME is in env -> change the value
	*/
	int	ret_value;

	ret_value = infile_management(data->input, envp);
	if (ret_value == -1)
		;
	ret_value = outfile_management(data->output);
	if (ret_value == -1)
		;

}
// int	expand_management(t_table *tokens, char **envp)
// {
// 	int				i_tok;
// 	enum e_rtype	type;

// 	i_tok = 0;
// 	while (i_tok < tokens->size)
// 	{
// 		type = find_type(tokens->tab[i_tok]);
// 		if (type == PIPE || type == HEREDOC || )
// 		if (tokens_treatment(&(tokens->tab[i_tok]), envp) == -1)
// 			return (-1);
// 		i_tok++;
// 		// if (tokens->tab[i_tok][i] >= 48 && tokens->tab[i_tok][i] <= 57)
// 		// {
// 		// 	if (cut_str(&(tokens->tab)[i_tok], start, (i + 1)) == -1) // ignore the $7 and keep the rest of the string
// 		// 		return (-1);
// 		// }
// 		// else if (tokens->tab[i_tok][i] == 9 || tokens->tab[i_tok][i] == 32)
// 		// 	return (0);
// 		// while (tokens->tab[i_tok][i] && tokens->tab[i_tok][i] != 9 && \
// 		// 	tokens->tab[i_tok][i] != 32 && tokens->tab[i_tok][i] != '|' && \
// 		// 	tokens->tab[i_tok][i] != '$' && tokens->tab[i_tok][i] != c)
// 		// 	i++;
// 		// if (extract_var(&(tokens->tab)[i_tok], envp, start, i) == -1) // change the value or cut it if not in envp
// 		// 	return (-1);
// 	}
// 	return (0);
// }

