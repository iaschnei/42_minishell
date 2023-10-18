/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:14:56 by acostes           #+#    #+#             */
/*   Updated: 2023/05/31 10:16:30 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief  count the pipes present in a tokens list
/// @return number of pipes found
size_t	count_pipes(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

/// @brief  creates and returns a list of pipes found in token,
///			declare their fd arrays and set their index as
///			the index in tokens list where the pipe is found
/// @return - pipes list if one or several pipes found in tokens
///			- NULL if no pipe found in tokens
t_pipe	*initialize_pipes(t_token *tokens, t_ms *ms)
{
	t_pipe	*pipes;
	t_pipe	*new_pipe;

	if (!ms || !tokens)
		return (NULL);
	pipes = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			new_pipe = pipe_new(tokens->index, &(ms->gc));
			if (!new_pipe)
				enomem_quit(ms);
			if (pipe(new_pipe->fd) == -1)
				enomem_quit(ms);
			pipe_add_back(&pipes, new_pipe);
		}
		tokens = tokens->next;
	}
	return (pipes);
}

/// @brief  closes all pipes file descriptors in pipes list
///			except the ones specified by the pointers fd_1 and fd_2
void	close_unused_pipe_fds(t_pipe *pipes, int *fd_1, int *fd_2, t_ms *ms)
{
	while (pipes)
	{
		if (pipes->fd[0] != *fd_1 && pipes->fd[0] != *fd_2)
		{
			if (close(pipes->fd[0]) == -1)
			{
				enomem_quit(ms);
			}
		}
		if (pipes->fd[1] != *fd_1 && pipes->fd[1] + 1 != *fd_2)
		{
			if (close(pipes->fd[1]) == -1)
			{
				enomem_quit(ms);
			}
		}
		pipes = pipes->next;
	}
}
