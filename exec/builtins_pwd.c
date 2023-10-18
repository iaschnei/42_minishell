/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:11:30 by acostes           #+#    #+#             */
/*   Updated: 2023/06/13 10:15:53 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reproduces behavior of "pwd" command
///			with no option.
void	ms_pwd(t_ms *ms)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		enomem_quit(ms);
	empty_mem(ms);
	if (ft_printf(1, "%s\n", cwd) == -1)
	{
		free(cwd);
		quit_shell(print_err(1, 1, "pwd",
				"write error: No space left on device\n"), ms, 0);
	}
	free(cwd);
	exit(0);
}
