/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:37:24 by acostes           #+#    #+#             */
/*   Updated: 2023/05/25 09:12:25 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief find if variable with name <name> exists in environment
///			and returns the node of <env> list where it is found
/// @return node of <env> list where <name> variable is found
///			NULL if <name> doesn't exist in <env> list
t_env	*find_in_env(char *name, t_env *env)
{
	while (env)
	{
		if (!str_isdiff(name, env->name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/// @brief initialize OLDPWD and PWD environment variables
///			if not set
/// @return working directory path as a string,
///			NULL if getcwd command failed.
char	*initialize_pwd(t_env **env, t_ms *ms)
{
	char	*wd;

	if (!find_in_env("OLDPWD", *env))
		env_add_back(env, env_new("OLDPWD", NULL, &(ms->gc)));
	wd = getcwd(NULL, 0);
	if (!wd)
		return (NULL);
	if (!find_in_env("PWD", *env))
	{
		env_add_back(env, env_new("PWD", wd, &(ms->gc)));
		return (wd);
	}
	gc_free(wd, NULL);
	return (find_in_env("PWD", *env)->val);
}

/// @brief search for environment variable with name <name>
///			in environment list <env>
///			and returns its value if found
/// @return value of environment variable if found,
///			NULL if no variable with name <name> exists
char	*get_env_var_val(char *name, t_env *env)
{
	t_env	*var;

	var = find_in_env(name, env);
	if (!var)
		return (NULL);
	return (var->val);
}

/// @brief search for environment variable with name <name>
///			in environment list <env>
///			and updates its value with a duplicate of <new_val> if found
/// @return duplicate of <new_val> if variable with name <name> exists,
///			NULL otherwise
char	*set_env_var_val(char *name, char *new_val, t_ms *ms)
{
	t_env	*var;

	var = find_in_env(name, ms->env);
	if (!var)
		return (NULL);
	gc_free(var->val, &(ms->gc));
	var->val = gc_strdup(new_val, &(ms->gc));
	if (!(var->val))
		enomem_quit(ms);
	return (var->val);
}

/// @brief In an expression of type "NAME", "NAME=" or "NAME=VAL",
///			create a string "<NAME>" and returns it if the name is valid
///			(a valid name contains only alphanumerical characters and "_",
///			and must not begin by a number)
/// @return name string upon success, NULL if not a valid name
char	*parse_env_var_name(char *var, t_ms *ms)
{
	char	*name;
	size_t	i;

	if (!(var[0]) || (var[0] && !ft_isalpha(var[0]) && var[0] != '_'))
	{
		print_err3(1, "export", var, "not a valid identifier\n");
		return (NULL);
	}
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			print_err3(1, "export", var, "not a valid identifier\n");
			return (NULL);
		}
		i++;
	}
	name = gc_malloc(i + 1, &(ms->gc));
	if (!name)
		enomem_quit(ms);
	ft_strlcpy(name, var, i + 1);
	return (name);
}
