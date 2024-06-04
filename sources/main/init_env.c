/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:04:08 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/27 09:25:35 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"
#include "main.h"

// ###### INCLUDES ######


// ###### PROTOTYPES ######

size_t	ft_perror(char *err_message);

// ###### PROTOTYPES ######

static char	*err_manager(char *env)
{
	size_t	i;

	i = 0;
	env = ft_calloc(sizeof(char), 4);
	if (!env)
		return (ft_perror(INIT_ERROR), exit(1), NULL);
	while (i < 3)
	{
		env[i] = '>';
		i++;
	}
	env[i] = ' ';
	return (env);
}

char	*init_env(void)
{
	size_t	i;
	char	*env;
	char	*real_secur;

	if (env)
		free(env);
	env = ft_strdup(getenv("PWD"));
	if (!env)
		err_manager(env);
	real_secur = ft_realloc(env, (ft_strlen(env) + 3), ft_strlen(env));
	if (!real_secur)
		return (free(env), err_manager(env));
	i = ft_strlen(real_secur);
	real_secur[i] = '$';
	real_secur[++i] = ' ';
	return (real_secur);
}
