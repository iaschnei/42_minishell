/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:17:20 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:43:56 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

///@brief   if there are no commands in a line, return an error
///			if PIPE_num > or < to (CMD_num - 1), error
int	incorrect_tokens(t_token *tok)
{
	while (tok)
	{
		if (((tok->type == PIPE) && (tok->index == 0 || !tok->next
					|| tok->next->type == PIPE)) || ((tok->type == R_IN
					|| tok->type == R_OUT || tok->type == R_OUT_APP
					|| tok->type == DELIM) && (!tok->next
					|| tok->next->type != FILENAME)))
		{
			print_err4(1, tok->text);
			return (1);
		}
		tok = tok->next;
	}
	return (0);
}

int	inside_quotes(char *line, int iter)
{
	int	tmp;
	int	start_of_quote;
	int	end_of_quote;

	tmp = 0;
	while (line[tmp])
	{
		if (line[tmp] == '\'' || line[tmp] == '"')
		{
			start_of_quote = tmp;
			end_of_quote = find_end_quote(line, tmp);
			if (line[tmp] == '"' && iter > start_of_quote
				&& iter < end_of_quote)
				return (1);
			if (line[tmp] == '\'' && iter > start_of_quote
				&& iter < end_of_quote)
				return (1);
		}
		tmp++;
	}
	return (0);
}

int	are_there_quotes(char *token)
{
	int		iter;

	iter = 0;
	while (token[iter])
	{
		if (token[iter] == '"' || token[iter] == '\'')
			return (1);
		iter++;
	}
	return (0);
}
