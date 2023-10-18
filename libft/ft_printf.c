/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:30:49 by acostes           #+#    #+#             */
/*   Updated: 2023/06/12 17:01:35 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_conversion(int fd, const char *fmt, int *i, va_list *args)
{
	int	printed;

	if (fmt[*i] == '%')
		printed = my_putchar(fd, '%');
	else if (fmt[*i] == 'c')
		printed = print_char(fd, args);
	else if (fmt[*i] == 's')
		printed = print_str(fd, args);
	else if (fmt[*i] == 'p')
		printed = print_ptr(fd, args);
	else if (fmt[*i] == 'd' || fmt[*i] == 'i')
		printed = print_int(fd, args);
	else if (fmt[*i] == 'u' || fmt[*i] == 'x' || fmt[*i] == 'X')
		printed = print_uint(fd, fmt[*i], args);
	else
		printed = -1;
	if (printed >= 0)
		(*i)++;
	return (printed);
}

int	print_loop(int fd, const char *fmt, va_list *args)
{
	int	i;
	int	printed;
	int	total_printed;

	i = 0;
	total_printed = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			printed = print_conversion(fd, fmt, &i, args);
			if (printed < 0)
				return (-1);
			total_printed += printed;
		}
		else
		{
			printed = my_putchar(fd, fmt[i++]);
			if (printed < 0)
				return (-1);
			total_printed++;
		}
	}
	return (total_printed);
}

int	ft_printf(int fd, const char *fmt, ...)
{
	va_list	args;
	int		total_printed;

	if (!fmt)
		return (-1);
	va_start(args, fmt);
	total_printed = print_loop(fd, fmt, &args);
	va_end(args);
	return (total_printed);
}
