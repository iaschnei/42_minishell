/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:02:36 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/12 15:57:00 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_redir_in(int redir_in, t_ms *ms)
{
	if (dup2(redir_in, STDIN_FILENO) == -1)
		enomem_quit(ms);
	if (close(redir_in) == -1)
		enomem_quit(ms);
}

static void	set_redir_out(int redir_out, t_ms *ms)
{
	if (dup2(redir_out, STDOUT_FILENO) == -1)
		enomem_quit(ms);
	if (close(redir_out) == -1)
		enomem_quit(ms);
}

static void	close_pipes_fd_in(int redir_in, int pipe_in_fd, t_ms *ms)
{
	if (pipe_in_fd != 0)
	{
		if (redir_in != -1 && pipe_in_fd != redir_in)
		{
			ms->has_redir_in = 1;
		}
	}
}

static void	close_pipes_fd_out(int redir_out, int pipe_out_fd, t_ms *ms)
{
	if (pipe_out_fd != 0)
	{
		if (redir_out != -1 && pipe_out_fd != redir_out)
		{
			if (close(pipe_out_fd) == -1)
				enomem_quit(ms);
		}
	}
}

/// @brief executes a subcommand, redirecting its I/O in pipes if existing
/// @param pipe_in = the previous pipe if it exists, otherwise is set to 0
/// @param pipe_out = the following pipe if it exists, otherwise is set to 0
/// NOTE: Pipe fds are set to 0 if they do not exist because of 
///		  get_redir_x_fd's logic
void	set_redirs(t_token *tok, t_pipe *pipe_in, t_pipe *pipe_out, t_ms *ms)
{
	int		redir_in;
	int		redir_out;
	int		pipe_in_fd;
	int		pipe_out_fd;

	if (!pipe_in)
		pipe_in_fd = 0;
	else
		pipe_in_fd = pipe_in->fd[0];
	if (!pipe_out)
		pipe_out_fd = 0;
	else
		pipe_out_fd = pipe_out->fd[1];
	redir_in = get_redir_in_fd(tok, pipe_in_fd, ms);
	redir_out = get_redir_out_fd(tok, pipe_out_fd);
	if (redir_in != -1)
		set_redir_in(redir_in, ms);
	if (redir_out != -1)
		set_redir_out(redir_out, ms);
	close_pipes_fd_in(redir_in, pipe_in_fd, ms);
	close_pipes_fd_out(redir_out, pipe_out_fd, ms);
}
