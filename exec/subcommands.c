/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:43:01 by acostes           #+#    #+#             */
/*   Updated: 2023/05/31 10:25:53 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_next_pipes_fd(t_pipe *pipe, t_ms *ms)
{
	while (pipe)
	{
		if (close(pipe->fd[0]) == -1)
			enomem_quit(ms);
		if (close(pipe->fd[1]) == -1)
			enomem_quit(ms);
		pipe = pipe->next;
	}
}

static void	close_next_pipes_fd_interm(t_pipe *pipe, t_ms *ms)
{
	if (close(pipe->fd[0]) == -1)
		enomem_quit(ms);
	pipe = pipe->next;
	while (pipe)
	{
		if (close(pipe->fd[0]) == -1)
			enomem_quit(ms);
		if (close(pipe->fd[1]) == -1)
			enomem_quit(ms);
		pipe = pipe->next;
	}
}

void	first_subcommand(t_pipe *pipe, int to_execute, t_ms *ms)
{
	if (must_be_forked(ms->tokens))
	{
		ms->pids[ms->pid_iter] = protected_fork(ms);
		if (ms->pids[ms->pid_iter] == 0)
		{
			close_next_pipes_fd(pipe->next, ms);
			if (close(pipe->fd[0]) == -1)
				enomem_quit(ms);
			set_redirs(ms->tokens, NULL, pipe, ms);
			if (to_execute)
				exec_command(ms->tokens, 0, ms);
		}
		ms->pid_iter++;
	}
	if (close(pipe->fd[1]) == -1)
		enomem_quit(ms);
}

void	intermediate_subcommand(t_pipe *pipe, int to_execute, t_ms *ms)
{
	if (must_be_forked(ms->tokens))
	{
		ms->pids[ms->pid_iter] = protected_fork(ms);
		if (ms->pids[ms->pid_iter] == 0)
		{
			close_next_pipes_fd_interm(pipe->next, ms);
			set_redirs(ms->tokens, pipe, pipe->next, ms);
			if (ms->has_redir_in)
			{
				if (close((pipe->fd)[0]) == -1)
					enomem_quit(ms);
			}
			if (to_execute)
				exec_command(ms->tokens, 0, ms);
		}
		ms->pid_iter++;
	}
	if (close((pipe->fd)[0]) == -1)
		enomem_quit(ms);
	if (close(pipe->next->fd[1]) == -1)
		enomem_quit(ms);
}

void	last_subcommand(t_pipe *pipe, int to_execute, t_ms *ms)
{
	if (must_be_forked(ms->tokens))
	{
		ms->pids[ms->pid_iter] = protected_fork(ms);
		if (ms->pids[ms->pid_iter] == 0)
		{
			set_redirs(ms->tokens, pipe, NULL, ms);
			if (ms->has_redir_in)
			{
				if (close((pipe->fd)[0]) == -1)
					enomem_quit(ms);
			}
			if (to_execute)
				exec_command(ms->tokens, 0, ms);
		}
		ms->pid_iter++;
	}
	if (close(pipe->fd[0]) == -1)
		enomem_quit(ms);
}
