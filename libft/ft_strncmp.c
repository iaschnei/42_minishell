/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:11:33 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 12:26:53 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	diff = 0;
	while (diff == 0 && i < n)
	{
		diff = (unsigned char) s1[i] - (unsigned char) s2[i];
		if (!s1[i] || !s2[i])
			return (diff);
		i++;
	}
	return (diff);
}
