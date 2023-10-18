/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:31:25 by acostes           #+#    #+#             */
/*   Updated: 2022/11/21 12:56:37 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i_dst;
	size_t	i_src;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size < dst_len + 1)
		return (size + src_len);
	i_src = 0;
	i_dst = dst_len;
	while (src[i_src] && i_dst < size - 1)
		dst[i_dst++] = src[i_src++];
	dst[i_dst] = 0;
	return (dst_len + src_len);
}
