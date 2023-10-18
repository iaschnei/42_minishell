/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:55:44 by acostes           #+#    #+#             */
/*   Updated: 2023/05/04 09:59:53 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	int_putnbr(int fd, int n)
{
	int	printed;

	printed = 0;
	if (n == -2147483648)
		return (my_putstr(fd, "-2147483648"));
	if (n < 0)
	{
		printed += my_putchar(fd, '-');
		printed += int_putnbr(fd, -n);
	}
	else if (n < 10)
		printed += my_putchar(fd, n + '0');
	else
	{
		printed += int_putnbr(fd, n / 10);
		printed += int_putnbr(fd, n % 10);
	}
	return (printed);
}

int	uint_putnbr_base(int fd, unsigned int n, char *base, int base_size)
{
	int	printed;

	printed = 0;
	if (n < (unsigned int) base_size)
		printed += my_putchar(fd, base[n]);
	else
	{
		printed += uint_putnbr_base(fd, n / base_size, base, base_size);
		printed += uint_putnbr_base(fd, n % base_size, base, base_size);
	}
	return (printed);
}

int	ullong_putnbr_base(int fd, unsigned long long n, char *base, int base_size)
{
	int	printed;

	printed = 0;
	if (n < (unsigned long long) base_size)
		printed += my_putchar(fd, base[n]);
	else
	{
		printed += ullong_putnbr_base(fd, n / base_size, base, base_size);
		printed += ullong_putnbr_base(fd, n % base_size, base, base_size);
	}
	return (printed);
}

int	print_int(int fd, va_list *args)
{
	int	nbr;

	nbr = va_arg(*args, int);
	return (int_putnbr(fd, nbr));
}

int	print_uint(int fd, char convertor, va_list *args)
{
	unsigned int	nbr;

	nbr = va_arg(*args, unsigned int);
	if (convertor == 'u')
		return (uint_putnbr_base(fd, nbr, "0123456789", 10));
	if (convertor == 'x')
		return (uint_putnbr_base(fd, nbr, "0123456789abcdef", 16));
	if (convertor == 'X')
		return (uint_putnbr_base(fd, nbr, "0123456789ABCDEF", 16));
	return (-1);
}
