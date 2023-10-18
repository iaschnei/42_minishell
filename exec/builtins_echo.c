/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:52:09 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/13 10:19:18 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reproduces behavior of "echo" command
///			with only "-n" flag implemented
///			when arguments are provided
static void	ms_echo_with_args(t_token *arg, t_ms *ms)
{
	int	n_flag;

	n_flag = 1;
	if (((char *)(arg->text))[0] == '-'
		&& has_only_char((char *)(arg->text) + 1, 'n'))
		arg = next_arg(arg);
	else
		n_flag = 0;
	while (arg)
	{
		print_if_possible(1, (char *) arg->text, "echo", ms);
		arg = next_arg(arg);
		if (arg)
			print_if_possible(1, " ", "echo", ms);
	}
	if (!n_flag)
		print_if_possible(1, "\n", "echo", ms);
}

/// @brief reproduces behavior of "echo" command
///			with only "-n" flag implemented.
void	ms_echo(t_token *token, t_ms *ms)
{
	t_token	*arg;

	arg = next_arg(token);
	if (!arg || !(char *)(arg->text))
	{
		if (ft_printf(1, "\n") == -1)
			quit_shell(print_err(1, 1, "echo",
					"write error: No space left on device\n"), ms, 0);
	}
	else
		ms_echo_with_args(arg, ms);
	empty_mem(ms);
	exit(0);
}
