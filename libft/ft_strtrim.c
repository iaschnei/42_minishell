/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:36:34 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 13:09:36 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_string(char c, char const *s)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*left_trim_substr(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (is_in_string(s1[i], set))
		i++;
	return ((char *) s1 + i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*left_trimmed;
	char	*right_trimmed;

	if (!s1)
		return (NULL);
	left_trimmed = left_trim_substr(s1, set);
	len = ft_strlen(left_trimmed);
	if (len == 0)
	{
		right_trimmed = malloc(1 * sizeof(char));
		if (right_trimmed == NULL)
			return (NULL);
		right_trimmed[0] = 0;
		return (right_trimmed);
	}
	i = len - 1;
	while (i > 0 && is_in_string(left_trimmed[i], set))
		i--;
	right_trimmed = malloc((i + 2) * sizeof(char));
	if (right_trimmed == NULL)
		return (NULL);
	ft_strlcpy(right_trimmed, left_trimmed, i + 2);
	return (right_trimmed);
}
