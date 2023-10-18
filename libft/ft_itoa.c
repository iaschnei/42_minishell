/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:00:09 by acostes           #+#    #+#             */
/*   Updated: 2023/04/27 17:16:28 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	recursive_itoa(char *s, int n, int *digit_idx)
{
	if (n >= 10)
	{
		recursive_itoa(s, n / 10, digit_idx);
		recursive_itoa(s, n % 10, digit_idx);
	}
	else
	{
		s[*digit_idx] = n + '0';
		(*digit_idx)++;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	if (n == -2147483648)
		s = ft_strdup("-2147483648");
	else
	{
		i = 0;
		s = malloc((nbr_len(n) + 1) * sizeof(char));
		if (s == NULL)
			return (NULL);
		if (n < 0)
		{
			s[i] = '-';
			n = -n;
			i++;
		}
		recursive_itoa(s, n, &i);
		s[i] = 0;
	}
	return (s);
}
