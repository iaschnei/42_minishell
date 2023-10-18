/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:49:48 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/13 10:19:34 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief executes builtin command
void	ms_builtin(t_token *token, int is_forked, t_ms *ms)
{
	if (!ms || !token)
		return ;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD)
		{
			if (!str_isdiff(token->text, "echo"))
				ms_echo(token, ms);
			else if (!str_isdiff(token->text, "exit"))
				ms_exit(token, ms);
			else if (!str_isdiff(token->text, "export"))
				ms_export(token, is_forked, ms);
			else if (!str_isdiff(token->text, "env"))
				ms_env(token, ms->env, ms);
			else if (!str_isdiff(token->text, "unset"))
				ms_unset(token, ms);
			else if (!str_isdiff(token->text, "pwd"))
				ms_pwd(ms);
			else if (!str_isdiff(token->text, "cd"))
				ms_cd(token, ms);
		}
		token = token->next;
	}
}

/// @brief checks if the command must be forked
/// @return 1 if command must be forked, 0 otherwise
int	must_be_forked(t_token *token)
{
	t_token	*arg;

	if (!str_isdiff(token->text, "export"))
	{
		arg = next_arg(token);
		if (!arg || !(char *)(arg->text))
			return (1);
		else
			return (0);
	}
	if (str_isdiff(token->text, "exit")
		&& str_isdiff(token->text, "unset")
		&& str_isdiff(token->text, "cd"))
		return (1);
	return (0);
}

/// @brief checks if the command in token corresponds to a builtin function
/// @return 1 if builtin, 0 otherwise
int	is_builtin(t_token *token)
{
	if (!str_isdiff(token->text, "echo")
		|| !str_isdiff(token->text, "exit")
		|| !str_isdiff(token->text, "export")
		|| !str_isdiff(token->text, "env")
		|| !str_isdiff(token->text, "unset")
		|| !str_isdiff(token->text, "pwd")
		|| !str_isdiff(token->text, "cd"))
		return (1);
	return (0);
}

void	print_if_possible(int fd, char *s, char *cmd_name, t_ms *ms)
{
	if (ft_printf(fd, "%s", s) == -1)
		quit_shell(print_err(1, 1, cmd_name,
				"write error: No space left on device\n"), ms, 0);
}

void	empty_mem(t_ms *ms)
{
	if (ms->gc)
		ft_lstclear(&(ms->gc), free);
	if (ms->line)
		gc_free(ms->line, &(ms->gc));
}
