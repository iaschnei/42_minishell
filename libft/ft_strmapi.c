/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:02:15 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 13:12:20 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new_s;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_s = malloc((len + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_s[i] = (*f)(i, s[i]);
		i++;
	}
	new_s[i] = 0;
	return (new_s);
}
