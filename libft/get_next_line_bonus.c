/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:40:02 by acostes           #+#    #+#             */
/*   Updated: 2023/01/12 17:05:32 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*gnl_error(char **stock, char *buf)
{
	if (buf)
		free(buf);
	if (*stock)
	{
		free(*stock);
		*stock = NULL;
	}
	return (NULL);
}

char	*end_of_file(char **stock, char *buf)
{
	char	*tmp;

	if (!*stock || **stock == 0)
		return (gnl_error(stock, buf));
	free(buf);
	tmp = *stock;
	*stock = NULL;
	return (tmp);
}

char	*dynamic_cat(char **stock, char *add)
{
	char	*new_stock;
	size_t	stock_len;
	size_t	total_size;

	stock_len = ft_strlen(*stock);
	total_size = stock_len + ft_strlen(add) + 1;
	new_stock = malloc(total_size);
	if (!new_stock)
		return (NULL);
	new_stock[0] = 0;
	if (*stock)
	{
		ft_strlcpy(new_stock, *stock, ft_strlen(*stock) + 1);
		free(*stock);
	}
	ft_strlcat(new_stock, add, total_size);
	*stock = new_stock;
	return (*stock);
}

char	*extract_line(char **stock, char *buf)
{
	char	*line;
	size_t	endofline_idx;
	size_t	new_stock_len;
	char	*new_stock;

	endofline_idx = find_endofline(*stock);
	line = ft_substr(*stock, 0, endofline_idx + 1);
	if (!line)
		return (gnl_error(stock, buf));
	new_stock_len = ft_strlen(*stock) - (endofline_idx + 1) + 1;
	new_stock = ft_substr(*stock, endofline_idx + 1, new_stock_len);
	free(*stock);
	*stock = new_stock;
	if (!*stock)
		return (gnl_error(stock, buf));
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stock[1048576];
	char		*buf;
	ssize_t		nbr_read;

	if (fd < 0 || fd > 1048575)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (gnl_error(stock + fd, buf));
	buf[0] = 0;
	while (find_endofline(stock[fd]) == -1)
	{
		nbr_read = read(fd, buf, BUFFER_SIZE);
		if (nbr_read == 0)
			return (end_of_file(stock + fd, buf));
		if (nbr_read == -1)
			return (gnl_error(stock + fd, buf));
		buf[nbr_read] = 0;
		stock[fd] = dynamic_cat(stock + fd, buf);
		if (!stock[fd])
			return (gnl_error(stock + fd, buf));
	}
	return (extract_line(stock + fd, buf));
}
