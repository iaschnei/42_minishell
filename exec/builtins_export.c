/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:11:23 by acostes           #+#    #+#             */
/*   Updated: 2023/06/13 10:14:54 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reproduces behavior of "export" command
///			with no option.
void	ms_export(t_token *token, int is_forked, t_ms *ms)
{
	t_token	*arg;

	arg = next_arg(token);
	if (!arg || !(char *)(arg->text))
	{
		env_sorted_print(ms->env, ms);
		if (is_forked)
		{
			empty_mem(ms);
			exit(0);
		}
		return ;
	}
	while (arg && (char *)(arg->text))
	{
		export_env_var((char *)(arg->text), ms);
		arg = next_arg(arg);
	}
	if (is_forked)
	{
		empty_mem(ms);
		exit(0);
	}
}
