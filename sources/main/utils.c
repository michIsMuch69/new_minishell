/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:56:02 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/22 11:06:36 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"
#include "main.h"

// ###### INCLUDES ######

size_t	ft_perror(char *err_message)
{
	return(write(2, err_message, ft_strlen(err_message)));
}

char	*get_pwd(void)
{
	size_t	i;
	char	*env;
	char	*real_secur;

	env = ft_strdup(getenv("PWD"));
	if (!env)
		return (ft_perror(INIT_ERROR), NULL);
	real_secur = ft_realloc(env, (ft_strlen(env) + 3), ft_strlen(env));
	if (!real_secur)
		return (free(env), ft_perror(INIT_ERROR), NULL);
	i = ft_strlen(real_secur);
	real_secur[i] = '$';
	real_secur[++i] = ' ';
	return (real_secur);
}
