/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:52:02 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:52:19 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief move to next arguments in the process' command,
///			skipping the file redirections, and stopping when
///			a pipe is encountered (or if the end of tokens list is reached).
/// @return the next argument as a token,
///			or NULL if end of command or pipe operator encountered.
t_token	*next_arg(t_token *token)
{
	if (!token)
		return (NULL);
	token = token->next;
	while (token && token->type != ARG)
	{
		if (token->type == PIPE)
			return (NULL);
		token = token->next;
	}
	return (token);
}

/// @brief returns first token of next subcommand in a multiple pipes command
/// @return first token of next subcommand
t_token	*next_command(t_token *tok)
{
	while (tok && tok->type != PIPE)
		tok = tok->next;
	if (tok->next)
		tok = tok->next;
	return (tok);
}
