/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:27:53 by acostes           #+#    #+#             */
/*   Updated: 2022/11/16 17:11:08 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				diff;
	unsigned char	*buf1;
	unsigned char	*buf2;

	buf1 = (unsigned char *) s1;
	buf2 = (unsigned char *) s2;
	i = 0;
	diff = 0;
	while (diff == 0 && i < n)
	{
		diff = buf1[i] - buf2[i];
		i++;
	}
	return (diff);
}
