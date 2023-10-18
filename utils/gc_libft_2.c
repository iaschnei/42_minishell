/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_libft_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:37:24 by acostes           #+#    #+#             */
/*   Updated: 2023/05/24 12:39:06 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gc_strjoin(char const *s1, char const *s2, t_list **gc)
{
	char	*join;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = gc_malloc((len1 + len2 + 1) * sizeof(char), gc);
	if (join == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		join[i + len1] = s2[i];
		i++;
	}
	join[i + len1] = 0;
	return (join);
}
