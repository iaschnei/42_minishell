/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:08:02 by acostes           #+#    #+#             */
/*   Updated: 2023/06/13 10:17:07 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reproduces behavior of "unset" command
///			with no option.
void	ms_unset(t_token *token, t_ms *ms)
{
	t_token	*arg;
	t_env	*var;

	arg = next_arg(token);
	while (arg && (char *)(arg->text))
	{
		var = find_in_env((char *)(arg->text), ms->env);
		if (var)
			env_var_delete(var, &(ms->env), ms);
		arg = next_arg(arg);
	}
	g_errnum = 0;
}
