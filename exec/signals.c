/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:59:32 by acostes           #+#    #+#             */
/*   Updated: 2023/06/01 08:17:54 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	(void) info;
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	(void) info;
	close(STDIN_FILENO);
	write(1, "\n", 1);
	g_errnum = -1;
}

void	handle_signals(void)
{
	struct sigaction	sigint_sa;
	sigset_t			sigset;

	sigemptyset(&sigset);
	sigint_sa.sa_mask = sigset;
	sigint_sa.sa_flags = SA_SIGINFO;
	sigint_sa.sa_sigaction = sigint_handler;
	sigaction(SIGINT, &sigint_sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_handle_signals(void)
{
	struct sigaction	sigint_sa;
	sigset_t			sigset;

	sigemptyset(&sigset);
	sigint_sa.sa_mask = sigset;
	sigint_sa.sa_flags = SA_SIGINFO;
	sigint_sa.sa_sigaction = heredoc_sigint_handler;
	sigaction(SIGINT, &sigint_sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
