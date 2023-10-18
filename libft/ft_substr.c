/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:40:20 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 13:08:25 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	initial_len;

	if (!s)
		return (NULL);
	initial_len = ft_strlen(s);
	if (start > initial_len)
	{
		substr = malloc(sizeof(char));
		substr[0] = 0;
		return (substr);
	}
	if (len > initial_len - start)
		len = initial_len - start;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
