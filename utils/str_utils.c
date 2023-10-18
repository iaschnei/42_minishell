/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:08:53 by acostes           #+#    #+#             */
/*   Updated: 2023/06/12 18:15:02 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief check if s1 and s2 are different
/// @return 1 if s1 != s2
///			-1 if error (one of the strings is NULL)
///			0 if the strings are equal
int	str_isdiff(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

/// @brief compares **non-NULL** strings s1 and s2 by ASCII order
///			(similar to strcmp)
/// @return result of the comparison s1 - s2
int	ft_strcmp(char *s1, char *s2)
{
	int		diff;
	size_t	i;

	diff = 0;
	i = 0;
	while (diff == 0)
	{
		diff = s1[i] - s2[i];
		if (!s1[i] || !s2[i])
			return (diff);
		i++;
	}
	return (diff);
}

/// @brief tests if every character of the string s is c
/// @return 1 if every character of the string s is c
///			0 otherwhise
int	has_only_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

/// @brief checks if argument arg
///			would be considered as a numeric argument by bash
/// @return 1 if considered as numeric
///			0 otherwise
int	is_arg_num(char *arg)
{
	size_t	i;

	if (!arg)
		return (0);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/// @brief checks if char c is present in string s
/// @return 1 if c present in s
///			0 otherwise
int	is_char_in_string(char c, char *s)
{
	size_t	i;

	i = 0;
	while (s[i++])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}
