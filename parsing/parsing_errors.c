/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:44:09 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:25:23 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_line(char *line, t_list **gc)
{
	gc_free(line, gc);
	write(2, "Error.\nThe line is invalid or couldn't be replaced.\n", 52);
	g_errnum = 42;
}

void	error_tokens(t_token *tok, t_list **gc)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok->next;
		gc_free(tok, gc);
		tok = tmp;
	}
	g_errnum = 43;
}
