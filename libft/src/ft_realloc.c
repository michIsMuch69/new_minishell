/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:01:42 by fberthou          #+#    #+#             */
/*   Updated: 2024/04/03 16:00:59 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/libft.h"

void	*ft_realloc(void *pointer, size_t memory_size, size_t src_size)
{
	void	*tmp;

	tmp = ft_calloc(memory_size, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = ft_memcpy(tmp, (const void *) pointer,
			src_size);
	if (pointer && pointer != tmp)
		free(pointer);
	return (tmp);
}
