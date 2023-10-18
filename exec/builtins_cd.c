/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:08:23 by acostes           #+#    #+#             */
/*   Updated: 2023/06/13 10:30:20 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief checks arguments of "cd" command and get from it
///			the path of destination working directory.
/// @return path of the working directory to move into,
///			or NULL upon error
static char	*ms_cd_get_new_wd(t_token *arg, char *old_wd, t_ms *ms)
{
	char	*new_wd;

	if (!arg || !(char *)(arg->text))
	{
		new_wd = get_env_var_val("HOME", ms->env);
		if (!new_wd)
		{
			gc_free(old_wd, NULL);
			print_err(1, 1, "cd", "HOME not set\n");
			return (NULL);
		}
	}
	else if (next_arg(arg))
	{
		gc_free(old_wd, NULL);
		print_err(1, 1, "cd", "too many arguments\n");
		return (NULL);
	}
	else if (!((char *)(arg->text))[0])
		return ("");
	else
		new_wd = arg->text;
	return (new_wd);
}

/// @brief moves the current directory to the path <new_wd> if existing,
///			and sets the env variables OLDPWD to <old_wd> and PWD to <new_wd>
///			upon success
/// @return 0 upon success, 1 upon error
static int	ms_cd_move_into_new_wd(char *old_wd, char *new_wd, t_ms *ms)
{
	int	ret;

	ret = chdir(new_wd);
	if (ret == -1)
	{
		gc_free(old_wd, NULL);
		return (print_err2(1, "cd", new_wd, "No such file or directory\n"));
	}
	set_env_var_val("OLDPWD", gc_strdup(old_wd, &(ms->gc)), ms);
	gc_free(old_wd, NULL);
	new_wd = getcwd(NULL, 0);
	if (!new_wd)
		enomem_quit(ms);
	set_env_var_val("PWD", gc_strdup(new_wd, &(ms->gc)), ms);
	gc_free(new_wd, NULL);
	g_errnum = 0;
	return (0);
}

/// @brief reproduces behavior of "cd" command
///			with no option.
int	ms_cd(t_token *token, t_ms *ms)
{
	t_token	*arg;
	char	*old_wd;
	char	*new_wd;

	old_wd = getcwd(NULL, 0);
	if (!old_wd)
		enomem_quit(ms);
	arg = next_arg(token);
	new_wd = ms_cd_get_new_wd(arg, old_wd, ms);
	if (!new_wd)
		return (1);
	else if (!new_wd[0])
		return (0);
	return (ms_cd_move_into_new_wd(old_wd, new_wd, ms));
}
