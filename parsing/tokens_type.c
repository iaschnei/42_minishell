/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:25:26 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:26:28 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

///@brief	determine the type of each token
int	determine_type(t_token *tokens)
{
	determine_pipes_and_redir(tokens);
	if (determine_filenames(tokens))
	{
		print_err4(1, determine_filenames(tokens));
		return (1);
	}
	if (determine_filenames_bis(tokens))
	{
		print_err4(1, determine_filenames_bis(tokens));
		return (1);
	}
	determine_cmd_and_arg(tokens);
	if (incorrect_tokens(tokens) == 1)
		return (1);
	return (0);
}

void	determine_pipes_and_redir(t_token *tok)
{
	while (tok)
	{
		if (tok->type == 0)
		{
			if (tok->text[0] == '|')
				tok->type = PIPE;
			else if (tok->text[0] == '<' && ft_strlen(tok->text) == 1)
				tok->type = R_IN;
			else if (tok->text[0] == '>' && ft_strlen(tok->text) == 1)
				tok->type = R_OUT;
			else if (tok->text[0] == '<' && ft_strlen(tok->text) == 2)
				tok->type = DELIM;
			else if (tok->text[0] == '>' && ft_strlen(tok->text) == 2)
				tok->type = R_OUT_APP;
		}
		tok = tok->next;
	}
	return ;
}

char	*determine_filenames(t_token *tok)
{
	while (tok->next)
	{
		if (tok->type == R_IN)
		{
			if (!tok->next)
				return (tok->text);
			if ((tok->next)->type != 0)
				return (tok->next->text);
			tok->next->type = FILENAME;
		}
		else if (tok->type == R_OUT)
		{
			if (!tok->next)
				return (tok->text);
			if ((tok->next)->type != 0)
				return (tok->next->text);
			tok->next->type = FILENAME;
		}
		tok = tok->next;
	}
	return (NULL);
}

char	*determine_filenames_bis(t_token *tok)
{
	while (tok->next)
	{
		if (tok->type == DELIM)
		{
			if (!tok->next)
				return (tok->text);
			if ((tok->next)->type != 0)
				return (tok->next->text);
			tok->next->type = FILENAME;
		}
		if (tok->type == R_OUT_APP)
		{
			if (!tok->next)
				return (tok->text);
			if ((tok->next)->type != 0)
				return (tok->next->text);
			tok->next->type = FILENAME;
		}
		tok = tok->next;
	}
	return (NULL);
}

void	determine_cmd_and_arg(t_token *tok)
{
	while (tok)
	{
		while (tok->type != 0 && tok->next)
			tok = tok->next;
		if (tok->type == 0)
			tok->type = CMD;
		if (tok->next)
			tok = tok->next;
		while (tok && tok->type == 0)
		{
			tok->type = ARG;
			tok = tok->next;
		}
		if (tok)
			tok = tok->next;
	}
}
