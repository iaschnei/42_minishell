/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:45:20 by acostes           #+#    #+#             */
/*   Updated: 2023/06/12 17:02:33 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	my_putchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	my_putstr(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (my_putchar(fd, s[i++]) == -1)
			return (-1);
	}
	return (i);
}

int	print_char(int fd, va_list *args)
{
	char	c;

	c = (char) va_arg(*args, int);
	return (my_putchar(fd, c));
}

int	print_str(int fd, va_list *args)
{
	char	*s;

	s = va_arg(*args, char *);
	if (!s)
	{
		return (my_putstr(fd, "(null)"));
	}
	return (my_putstr(fd, s));
}

int	print_ptr(int fd, va_list *args)
{
	unsigned long long	ptr;
	int					printed;

	printed = 0;
	ptr = (unsigned long long) va_arg(*args, void *);
	if (!ptr)
	{
		return (my_putstr(fd, "(nil)"));
	}
	printed += my_putstr(fd, "0x");
	printed += ullong_putnbr_base(fd, ptr, "0123456789abcdef", 16);
	return (printed);
}
