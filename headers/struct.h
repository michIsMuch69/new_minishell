/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:16:08 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/31 12:09:37 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <stdbool.h>

typedef struct s_table
{
	char	**tab;
	int		size;
} t_table;

enum e_rtype
{
	ERROR = -1,
	COMMAND,
	PIPE,
	DELIMITER,
	APPEND,
	INFILE,
	OUTFILE
};

typedef struct s_redir
{
	enum e_rtype	type;
	char			*filename;
	bool			in_out;
	struct s_redir	*next;
} t_redir;

typedef struct s_data
{
	enum e_rtype	cmd_type;
	char			*cmd;
	t_table			args;
	t_table			env;
	t_redir			*redir;
} t_data;

#endif
