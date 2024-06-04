/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:16:08 by fberthou          #+#    #+#             */
/*   Updated: 2024/06/04 09:37:28 by jedusser         ###   ########.fr       */
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
	char		*cmd; // chemin commande non init
		

}	t_data;

typedef struct s_table
{
	char	**tab;
	size_t	size;
} t_table;

#endif