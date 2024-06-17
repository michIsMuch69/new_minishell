/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:34:17 by jedusser          #+#    #+#             */
/*   Updated: 2024/06/06 09:53:16 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

//check_vars;
//check file;

void	echo(char *arguments)
{
	char	**to_echo;
	int		i;

	to_echo = ft_split(arguments, ' ');
	i = 0;
	while (to_echo[i])
	{
		putstring(to_echo[i]);
		if (i + 1 != 0)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}
