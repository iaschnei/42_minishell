/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:29:41 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 12:25:56 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src || !dest)
		return (dest);
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			((char *) dest)[i] = ((const char *) src)[i];
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			((char *) dest)[n - i - 1] = ((const char *) src)[n - i - 1];
			i++;
		}
	}
	return (dest);
}
