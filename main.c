/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:28:16 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/01 10:08:22 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errnum = 0;

/// @brief Initialize ms structures
void	ms_init(t_ms *ms)
{
	ms->gc = NULL;
	ms->line = NULL;
	ms->tokens = NULL;
	ms->heredoc = NULL;
	ms->pids = NULL;
	ms->pid_iter = 0;
	ms->stdin_save = 0;
	ms->has_redir_in = 0;
}

void	free_line(t_ms *ms)
{
	free(ms->line);
	free_tokens(ms->tokens, &(ms->gc));
	free_tokens(ms->heredoc, &(ms->gc));
	ms->tokens = NULL;
	ms->heredoc = NULL;
}

static void	loop_process(t_ms *ms)
{
	ms->stdin_save = dup(STDIN_FILENO);
	ms->line = readline("minishell>");
	if (!(ms->line))
		quit_shell(0, ms, 1);
	if (*(ms->line))
		add_history(ms->line);
	ms->tokens = parsing(ms->line, ms->env, &(ms->gc), ms);
	ms->head = ms->tokens;
	ms->heredoc_num = 0;
	heredoc_handle_signals();
	heredoc(ms, ms->tokens);
	if (g_errnum != -1)
	{
		handle_signals();
		if (close(ms->stdin_save) == -1)
			enomem_quit(ms);
		exec_line(ms);
	}
	else
	{
		g_errnum = 130;
		dup2(ms->stdin_save, STDIN_FILENO);
		if (close(ms->stdin_save) == -1)
			enomem_quit(ms);
	}
}

int	main(int ac, char **av, char **env)
{
	t_ms	ms;
	char	*wd;

	(void) ac;
	(void) av;
	ms_init(&ms);
	handle_signals();
	ms.env = initialise_env(env, &(ms.gc));
	wd = initialize_pwd(&(ms.env), &ms);
	set_sh_level(&ms);
	if (!wd)
		enomem_quit(&ms);
	while (1)
	{
		loop_process(&ms);
		handle_signals();
		free_line(&ms);
	}
	return (0);
}
