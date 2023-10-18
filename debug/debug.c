/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:10:01 by acostes           #+#    #+#             */
/*   Updated: 2023/06/01 08:34:13 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	show_fds(t_pipe *pipes)
{
	while (pipes)
	{
		ft_printf(2, "fd %i\n", pipes->fd[0]);
		ft_printf(2, "fd %i\n", pipes->fd[1]);
		pipes = pipes->next;
	}
}

void	show_list(t_list *lst)
{
	while (lst)
	{
		ft_printf(2, "%s\n", lst->content);
		lst = lst->next;
	}
}

void	print_heredoc(t_token *heredoc)
{
	while (heredoc)
	{
		ft_printf(2, "%s\n", heredoc->text);
		heredoc = heredoc->next;
	}
}
