/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:39:34 by acostes           #+#    #+#             */
/*   Updated: 2023/06/01 08:30:57 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief frees all and exit minishell
void	quit_shell(unsigned char errcode, t_ms *ms, int exit_msg)
{
	g_errnum = errcode;
	if (ms->gc)
		ft_lstclear(&(ms->gc), free);
	if (ms->line)
		gc_free(ms->line, &(ms->gc));
	if (exit_msg)
		write(2, "exit\n", 5);
	exit((int) errcode);
}

/// @brief quit shell upon ENOMEM error
void	enomem_quit(t_ms *ms)
{
	g_errnum = 12;
	write(2, "minishell: not enough memory\n", 29);
	quit_shell(12, ms, 1);
}

int	com_not_found(char *arg, t_ms *ms)
{
	print_err(127, 0, arg, "command not found\n");
	empty_mem(ms);
	exit(g_errnum);
	return (1);
}

int	no_such_file(char *arg, t_ms *ms)
{
	print_err(127, 1, arg, "No such file or directory\n");
	empty_mem(ms);
	exit(g_errnum);
	return (1);
}
