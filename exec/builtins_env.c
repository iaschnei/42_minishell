/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:10:08 by acostes           #+#    #+#             */
/*   Updated: 2023/06/13 10:13:02 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reproduces behavior of "env" command
///			with no option or argument.
void	ms_env(t_token *token, t_env *env, t_ms *ms)
{
	t_token	*arg;

	arg = next_arg(token);
	if (!arg || !(char *)(arg->text))
	{
		while (env)
		{
			env_var_print(env, 0, ms);
			env = env->next;
		}
		empty_mem(ms);
		exit(0);
	}
	else
		exit(print_err(1, 1, "env", "too many arguments\n"));
}
