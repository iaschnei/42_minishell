/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:12:33 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 14:37:50 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	mem_size;

	if (size != 0 && (nmemb * size) / size != nmemb)
	{
		return (NULL);
	}
	else
	{
		mem_size = nmemb * size;
		ptr = malloc(mem_size);
	}
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, mem_size);
	return (ptr);
}
