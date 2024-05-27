/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:16:08 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/25 17:17:06 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_type
{
	BUILTINS,
	H_DOC,
	D_LIMITER,
	E_VAR
};

typedef struct s_data
{
	enum e_type	cmd_type;
	char		*cmd;
	char		*opt;
	char		**args;
	char		*infile;
	char		*outfile;
}	t_data;

#endif