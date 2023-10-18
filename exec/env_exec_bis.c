/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 13:06:50 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/12 17:18:13 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief In an expression of type "NAME", "NAME=" or "NAME=VAL",
///			- stores the name and value in the end of env list if not existing,
///			- or updates its value if already existing
///			The "name" and "val" components of the new element in the list
///			are filled as following:
///				- "NAME"		=> name = NAME ; val = NULL
///				- "NAME="		=> name = NAME ; val = ""
///				- "NAME=VAL"	=> name = NAME ; val = VAL
/// @return name upon success, NULL if name is not a valid identifier
char	*export_env_var(char *var, t_ms *ms)
{
	char	*name;
	char	*val;
	size_t	name_len;

	name = parse_env_var_name(var, ms);
	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	if (var[name_len] != '=')
		val = NULL;
	else
	{
		val = gc_substr(var, name_len + 1, ft_strlen(var), &(ms->gc));
		if (!val)
			enomem_quit(ms);
	}
	if (!find_in_env(name, ms->env))
		env_add_back(&(ms->env), env_new(name, val, &(ms->gc)));
	else if (val)
		find_in_env(name, ms->env)->val = val;
	return (name);
}

/// @brief prints the environment variable given in argument, using:
///			"export" command output syntax if declare == 1
///			"env" command output syntax otherwise
/// @param env
/// @param declare
void	env_var_print(t_env *env, int declare, t_ms *ms)
{
	if (!env)
		return ;
	if (declare)
	{
		if (!(env->val))
		{
			if (ft_printf(1, "declare -x %s\n", env->name) == -1)
				quit_shell(print_err(1, 1, "export",
						"write error: No space left on device\n"), ms, 0);
		}
		else if (ft_printf(1, "declare -x %s=\"%s\"\n", env->name, env->val) == -1)
			quit_shell(print_err(1, 1, "export",
					"write error: No space left on device\n"), ms, 0);
	}
	else
	{
		if (env->val)
		{
			if (ft_printf(1, "%s=%s\n", env->name, env->val) == -1)
				quit_shell(print_err(1, 1, "env",
						"write error: No space left on device\n"), ms, 0);
		}
	}
}

/// @brief sorts a tab of environment variables by name in ASCII order
void	sort_env_tab(t_env *env_tab, size_t tab_len)
{
	size_t	bubble_sort_loop;
	size_t	i;
	t_env	buffer;

	bubble_sort_loop = 0;
	while (bubble_sort_loop < tab_len - 1)
	{
		i = 0;
		while (i < tab_len - bubble_sort_loop - 1)
		{
			if (ft_strcmp(env_tab[i].name, env_tab[i + 1].name) > 0)
			{
				buffer = env_tab[i];
				env_tab[i] = env_tab[i + 1];
				env_tab[i + 1] = buffer;
			}
			i++;
		}
		bubble_sort_loop++;
	}
}

/// @brief prints environment variables as expected by "export" command:
///			- with a "declare" syntax
///			- sorted by name in ASCII ascending order
void	env_sorted_print(t_env *env, t_ms *ms)
{
	t_env	*env_tab;
	size_t	i;
	size_t	tab_len;

	if (!env)
		return ;
	env_tab = malloc(env_size(env) * (sizeof(t_env)));
	if (!env_tab)
		enomem_quit(ms);
	i = 0;
	while (env)
	{
		env_tab[i++] = *env;
		env = env->next;
	}
	tab_len = i;
	sort_env_tab(env_tab, tab_len);
	i = 0;
	while (i < tab_len)
		env_var_print(&(env_tab[i++]), 1, ms);
	free(env_tab);
}

/// @brief increments SHLVL env variable if existing,
///			or create and initialize it to 1 otherwise
void	set_sh_level(t_ms *ms)
{
	t_env	*var;
	int		shell_level;
	char	*new_value;

	var = find_in_env("SHLVL", ms->env);
	if (!var)
	{
		export_env_var("SHLVL=1", ms);
		return ;
	}
	shell_level = ft_atoi(var->val);
	shell_level++;
	new_value = ft_itoa(shell_level);
	if (!new_value)
		enomem_quit(ms);
	set_env_var_val("SHLVL", new_value, ms);
	gc_free(new_value, NULL);
}
