/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:57:33 by acostes           #+#    #+#             */
/*   Updated: 2023/04/12 10:09:06 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

size_t	max(size_t a, size_t b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}
