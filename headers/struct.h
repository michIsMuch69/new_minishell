/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:16:08 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/29 17:01:26 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_type
{
	ERROR = -1,
	COMMAND,
	BUILTINS,
	H_DOC,
	D_LIMITER,
	E_VAR,
	PIPE
} ;

typedef struct s_infile
{
	char			*filename;
	struct s_infile	*next;
}	t_infile;

typedef struct s_outfile
{
	char				*filename;
	struct s_outfile	*next;
}	t_outfile;

typedef struct s_data
{
	enum e_type	cmd_type;
	char		*cmd;
	
	char		**opt;
	char		**args;

	t_infile	*infile;
	t_outfile	*outfile;
}	t_data;

typedef struct s_table
{
	char	**tab;
	size_t	size;
} t_table;

#endif