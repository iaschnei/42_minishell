/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:10:26 by acostes           #+#    #+#             */
/*   Updated: 2023/06/13 10:15:29 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reproduces behavior of "exit" command
///			with no option.
/// CHANGED: added a return to "if (next_arg(arg))" to make sure it doesnt
///			 quit when it shouldnt
int	ms_exit(t_token *token, t_ms *ms)
{
	t_token	*arg;
	t_token	*parse;

	parse = ms->head;
	while (parse)
	{
		if (parse->type == PIPE)
			return (1);
		parse = parse->next;
	}
	arg = next_arg(token);
	if (!arg || !(char *)(arg->text))
		quit_shell(0, ms, 1);
	if (!is_arg_num((char *)(arg->text)))
	{
		write(2, "exit\n", 5);
		quit_shell(print_err(2, 1, "exit", "numeric argument required\n"),
			ms, 0);
	}
	if (next_arg(arg))
	{
		write(2, "exit\n", 5);
		return (print_err(1, 1, "exit", "too many arguments\n"), 1);
	}
	return (quit_shell(ft_atoi((char *)(arg->text)), ms, 1), 0);
}
