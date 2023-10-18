/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:00:30 by acostes           #+#    #+#             */
/*   Updated: 2023/06/12 15:52:51 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	*initialise_pids(t_token *tokens, t_ms *ms)
{
	int		command_count;
	pid_t	*ret;

	gc_free(ms->pids, &(ms->gc));
	ms->pid_iter = 0;
	command_count = 0;
	while (tokens)
	{
		if (tokens->type == CMD && must_be_forked(tokens))
			command_count++;
		tokens = tokens->next;
	}
	ret = gc_malloc(command_count * sizeof(pid_t), &(ms->gc));
	if (!ret)
		return (enomem_quit(ms), NULL);
	return (ret);
}

/// @brief fork a process and quit if failed
/// @return forked pid
pid_t	protected_fork(t_ms *ms)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		enomem_quit(ms);
	else if (pid != 0)
		ignore_signals();
	return (pid);
}

pid_t	waitpid_and_set_exit_status(pid_t pid)
{
	int		wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		g_errnum = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 2)
	{
		g_errnum = 128 + WTERMSIG(wstatus);
		write(2, "\n", 1);
	}
	return (pid);
}

void	wait_all_pids(t_ms *ms)
{
	int	local_iter;

	local_iter = 0;
	while (local_iter < ms->pid_iter)
	{
		waitpid_and_set_exit_status(ms->pids[local_iter]);
		local_iter++;
	}
}

int	has_cmd(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type == CMD)
			return (1);
		token = token->next;
	}
	return (0);
}
