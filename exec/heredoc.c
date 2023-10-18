/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:42:18 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/01 09:45:22 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief  Parses tokens for "<<" then fill ms->heredoc with the last heredoc
///         inputs
void	heredoc(t_ms *ms, t_token *tokens)
{
	t_list	*keywds;
	t_list	*first;

	keywds = NULL;
	while (tokens)
	{
		if (tokens->type == DELIM)
		{
			ft_lstadd_back(&keywds, gc_lstnew(tokens->next->text, &(ms->gc)));
		}
		tokens = tokens->next;
	}
	first = keywds;
	while (keywds)
	{
		add_to_memory_heredoc(ms, keywds->content);
		if (g_errnum != -1)
		{
			keywds = keywds->next;
			token_add_back(&(ms->heredoc), token_new(NULL, 0, &(ms->gc)));
		}
		else
			break ;
	}
	gc_lstclear(&first, &(ms->gc));
}

/// @brief  Prompts the user for input until finding the keyword
///         And add each input to ms->heredoc
void	add_to_memory_heredoc(t_ms *ms, char *keyword)
{
	char		*line;
	char		*store_value;
	t_parsing	*data;

	line = NULL;
	while (g_errnum != -1)
	{
		rl_on_new_line();
		line = readline("> ");
		if (g_errnum != -1)
		{
			store_value = read_heredoc_prompt(ms, line, keyword);
			if (!store_value || !str_isdiff(line, keyword))
				break ;
			data = replace_var_line(store_value, ms->env, &(ms->gc));
			token_add_back(&(ms->heredoc),
				token_new(data->replaced, 0, (&ms->gc)));
			gc_free(line, NULL);
		}
	}
	gc_free(line, NULL);
}

char	*read_heredoc_prompt(t_ms *ms, char *line, char *keyword)
{
	char	*store_value;

	if (!line)
	{
		print_heredoc_warning(keyword);
		return (NULL);
	}
	store_value = gc_strdup(line, &(ms->gc));
	if (!store_value)
		enomem_quit(ms);
	return (store_value);
}

int	write_heredoc_to_pipe(t_token *heredoc, t_ms *ms)
{
	int	pipe_fd[2];
	int	heredoc_iter;

	heredoc_iter = 1;
	if (pipe(pipe_fd) == -1)
		enomem_quit(ms);
	while (heredoc_iter != ms->heredoc_num)
	{
		while (heredoc && heredoc->text)
			heredoc = heredoc->next;
		if (heredoc->next)
			heredoc = heredoc->next;
		heredoc_iter++;
	}
	while (heredoc && heredoc->text)
	{
		ft_printf(pipe_fd[1], "%s\n", heredoc->text);
		heredoc = heredoc->next;
	}
	if (heredoc->next)
		heredoc = heredoc->next;
	if (close(pipe_fd[1]) == -1)
		enomem_quit(ms);
	return (pipe_fd[0]);
}

int	get_heredoc_num(t_token *tokens, int max_index)
{
	int	ret;

	ret = 0;
	while (tokens && tokens->index < max_index)
	{
		if (tokens->type == DELIM)
			ret++;
		tokens = tokens->next;
	}
	return (ret);
}
