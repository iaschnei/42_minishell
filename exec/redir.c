/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:24:17 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/12 15:24:20 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief same behavior as open(path, oflag, 0644)
///			but closes the file descriptor afterwards
///			(if open succeeded)
/// @return -1 if open failed, file descriptor otherwise
int	open_close(char *path, int oflag, t_ms *ms)
{
	int	fd;

	fd = open(path, oflag, 0644);
	if (fd != -1)
	{
		if (close(fd) == -1)
			enomem_quit(ms);
	}
	return (fd);
}

/// @brief calls check_and_create_files()
///			and prints the first error found if so.
///	@return 0 if an error was found, 1 otherwise
int	check_files(t_token *tok, t_ms *ms)
{
	char	*error_filename;

	error_filename = check_and_create_files(tok, ms);
	if (error_filename)
	{
		if (access(error_filename, F_OK) != 0)
			print_err(1, 1, error_filename, "No such file or directory\n");
		else if (access(error_filename, R_OK) != 0
			|| access(error_filename, W_OK) != 0)
			print_err(1, 1, error_filename, "Permission denied\n");
		return (0);
	}
	return (1);
}

/// @brief  check if files in command exist
///			and if we have the right permissions to use it.
///			for each output file path found in the command,
///			the file is created if not existing
///			(except for file paths placed after a file token returning an error)
/// @return NULL if everything is fine, otherwise name of the first
///			filename that causes an error (for error message in check_files())
char	*check_and_create_files(t_token *tok, t_ms *ms)
{
	int		fd;

	while (tok && tok->type != PIPE)
	{
		if (tok->type == R_IN)
		{
			if (access(tok->next->text, F_OK | R_OK) == -1)
				return (tok->next->text);
		}
		if (tok->type == R_OUT)
		{
			fd = open_close(tok->next->text, O_CREAT | O_RDWR | O_TRUNC, ms);
			if (fd == -1)
				return (tok->next->text);
		}
		if (tok->type == R_OUT_APP)
		{
			fd = open_close(tok->next->text, O_CREAT | O_RDWR | O_APPEND, ms);
			if (fd == -1)
				return (tok->next->text);
		}
		tok = tok->next;
	}
	return (NULL);
}

/// Pass in the tokens starting from the first token of the subcommand
/// and pass the preceding pipe_fd or STDIN if it's the first command
int	get_redir_in_fd(t_token *tokens, int pipe_fd, t_ms *ms)
{
	t_token	*filename_token;
	int		index;

	filename_token = NULL;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == R_IN || tokens->type == DELIM)
			filename_token = tokens;
		index = tokens->index;
		tokens = tokens->next;
	}
	ms->heredoc_num = get_heredoc_num(ms->head, index);
	if (filename_token)
	{
		if (filename_token->type == DELIM)
			return (write_heredoc_to_pipe(ms->heredoc, ms));
		else if (filename_token->type == R_IN)
			return (open(filename_token->next->text, O_RDONLY));
	}
	if (pipe_fd != 0)
		return (pipe_fd);
	return (-1);
}

/// Pass in the tokens starting from the first token of the subcommand
/// and pass the folowing pipe_fd or STDOUT if it's the last command
int	get_redir_out_fd(t_token *tokens, int pipe_fd)
{
	t_token	*filename_token;

	filename_token = NULL;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == R_OUT || tokens->type == R_OUT_APP)
			filename_token = tokens;
		tokens = tokens->next;
	}
	if (filename_token)
	{
		if (filename_token->type == R_OUT)
			return (open(filename_token->next->text,
					O_CREAT | O_RDWR | O_TRUNC, 0644));
		else if (filename_token->type == R_OUT_APP)
			return (open(filename_token->next->text,
					O_CREAT | O_RDWR | O_APPEND, 0644));
	}
	if (pipe_fd != 0)
		return (pipe_fd);
	return (-1);
}
