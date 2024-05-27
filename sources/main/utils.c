/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:56:02 by fberthou          #+#    #+#             */
/*   Updated: 2024/05/27 08:10:49 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ###### INCLUDES ######

#include <stdlib.h>
#include "libft.h"

// ###### INCLUDES ######

size_t	ft_perror(char *err_message)
{
	return(write(2, err_message, ft_strlen(err_message)));
}
