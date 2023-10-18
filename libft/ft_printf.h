/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:31:20 by acostes           #+#    #+#             */
/*   Updated: 2023/05/04 10:01:47 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	my_putchar(int fd, char c);
int	my_putstr(int fd, char *s);
int	print_char(int fd, va_list *args);
int	print_str(int fd, va_list *args);
int	print_ptr(int fd, va_list *args);
int	int_putnbr(int fd, int n);
int	uint_putnbr_base(int fd, unsigned int n, char *base, int base_size);
int	ullong_putnbr_base(int fd, unsigned long long n, char *base, int base_size);
int	print_int(int fd, va_list *args);
int	print_uint(int fd, char convertor, va_list *args);
int	print_conversion(int fd, const char *fmt, int *i, va_list *args);
int	ft_printf(int fd, const char *fmt, ...);

#endif
