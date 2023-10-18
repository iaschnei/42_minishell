/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_line_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:58:39 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/04 10:13:38 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if the line is valid (no quotes error)
int	is_line_valid(char *line)
{
	int	iter;

	iter = 0;
	while (line[iter])
	{
		if (line[iter] == 39 || line[iter] == '"')
			iter = find_end_quote(line, iter);
		if (iter == -1)
			return (0);
		iter++;
	}
	return (1);
}

/// @brief 	find the ending of the quoting
/// @return returns -1 if it cant find a quote (=invalid line)
int	find_end_quote(char *line, int iter)
{
	char	quote;

	quote = line[iter];
	iter++;
	while (line[iter])
	{
		if (line[iter] == quote)
			return (iter);
		iter++;
	}
	return (-1);
}

/// @brief 	checks if we are inside a single quote or not
int	in_single_quote(char *line, int iter)
{
	int	tmp;
	int	start_of_quote;
	int	end_of_quote;

	tmp = 0;
	while (line[tmp])
	{
		if (line[tmp] == 39 || line[tmp] == '"')
		{
			start_of_quote = tmp;
			end_of_quote = find_end_quote(line, tmp);
			if (line[tmp] == '"' && iter > start_of_quote
				&& iter < end_of_quote)
				return (0);
			if (line[tmp] == 39 && iter > start_of_quote
				&& iter < end_of_quote)
				return (1);
		}
		tmp++;
	}
	return (0);
}

void	dollar_question(t_parsing *p_data)
{
	char	*num_str;
	int		num_iter;

	num_iter = 0;
	num_str = ft_itoa(g_errnum);
	if (!num_str)
		return ;
	while (num_iter < (int) ft_strlen(num_str))
	{
		p_data->replaced[p_data->replaced_iter] = num_str[num_iter];
		num_iter++;
		p_data->replaced_iter++;
	}
	p_data->original_iter += 2;
	gc_free(num_str, NULL);
}
