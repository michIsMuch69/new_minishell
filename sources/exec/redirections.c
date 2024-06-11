/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:47:54 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/11 08:48:06 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "exec.h"

char	*skip_redir_symbol(char *token_file, bool direction)
{
	char	*file;
	int		i;
	int		tok_nb;
	int		size;

	if (direction == 1)
		tok_nb = arrow_count(token_file, '>');
	else
		tok_nb = arrow_count(token_file, '<');
	printf("tok-nb == %d\n",tok_nb -1);
	if (tok_nb > 3)
		return (NULL);
	size = (ft_strlen(token_file) - tok_nb) + 1;
	file = ft_calloc(size, sizeof(char));
	if (!file)
		return (NULL);
	file = ft_strcpy(file, &token_file[tok_nb - 1]);
	printf("file == %s\n", file);
	return (file);
}

int	redir_input(t_data *data, int i, int prev_fd)
{
	int		input_fd;
	char	*input_file;

	if (data[i].input.size)
	{
		input_file = skip_redir_symbol(data[i].input.tab[0], 0);
		input_fd = open(input_file, O_RDONLY);
		if (input_fd == -1)
			return (perror("Failed to open input file"), -1);
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return (perror("Failed to redirect standard input"), close(input_fd), -1);
	}
	else if (i > 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			return (perror("Failed to duplicate previous fd for  input"), -1);
		close(prev_fd);
	}
	return (0);
}

int	redir_output(t_data *data, int i, int tab_size, int *fds)
{
	int		output_fd;
	char	*output_file;

	if (data[i].output.size)
	{
		output_file = skip_redir_symbol(data[i].output.tab[0], 1);
		if (arrow_count(data[i].output.tab[0], '>') - 1 == 1)
			output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (arrow_count(data[i].output.tab[0], '>') - 1 == 2)
			output_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (output_fd == -1)
			return (perror("Failed to open output file"), -1);
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return (perror("Failed to redirect standard output"), -1);
		close(output_fd);
	}
	else if (i < tab_size - 1)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (perror("Failed to duplicate pipe fd for output"), -1);
		close(fds[1]);
	}
	return (0);
}