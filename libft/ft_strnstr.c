/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:17:03 by acostes           #+#    #+#             */
/*   Updated: 2022/11/15 12:08:32 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_len;
	size_t	little_len;
	size_t	i;

	if (little[0] == 0)
		return ((char *) big);
	little_len = ft_strlen(little);
	if (little_len > len)
		return (NULL);
	big_len = ft_strlen(big);
	if (little_len > big_len)
		return (NULL);
	i = 0;
	while (i < len && i < big_len)
	{
		if (little_len > len - i)
			return (NULL);
		if (ft_strncmp(big + i, little, little_len) == 0)
			return ((char *) big + i);
		i++;
	}
	return (NULL);
}
