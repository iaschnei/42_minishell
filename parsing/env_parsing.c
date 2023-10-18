/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:12:12 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/30 10:30:32 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief	create a struct based on **env to store the name and the value
///			separatly
t_env	*initialise_env(char **env, t_list **gc)
{
	int		var_iter;
	char	*name;
	char	*val;
	t_env	*env_struct;

	env_struct = NULL;
	var_iter = 0;
	while (env[var_iter])
	{
		name = extract_env_var_name(env, var_iter, gc);
		if (!name)
			return (NULL);
		val = extract_env_var_val(env, var_iter, gc);
		if (!val)
			return (NULL);
		env_add_back(&env_struct, env_new(name, val, gc));
		var_iter++;
	}
	return (env_struct);
}

/// @brief	extract the env variable name from **env according to our current
///			iteration over **env
char	*extract_env_var_name(char **env, int var_iter, t_list **gc)
{
	char	*ret;
	int		iter;
	int		ret_len;

	ret_len = 0;
	iter = 0;
	while (env[var_iter][ret_len] != '=')
		ret_len++;
	ret = (char *)gc_malloc((ret_len + 1) * sizeof(char), gc);
	if (!ret)
		return (NULL);
	while (env[var_iter][iter] != '=')
	{
		ret[iter] = env[var_iter][iter];
		iter++;
	}
	ret[iter] = 0;
	return (ret);
}

/// @brief	extract the env value from **env according to our current
///			iteration over **env
char	*extract_env_var_val(char **env, int var_iter, t_list **gc)
{
	char	*ret;
	int		iter;
	int		tmp;
	int		ret_len;

	ret_len = 0;
	iter = 0;
	tmp = 0;
	while (env[var_iter][tmp] != '=')
		tmp++;
	tmp += 1;
	while (env[var_iter][tmp + ret_len])
		ret_len++;
	ret = (char *)gc_malloc((ret_len + 1) * sizeof(char), gc);
	if (!ret)
		return (NULL);
	while (env[var_iter][tmp + iter])
	{
		ret[iter] = env[var_iter][tmp + iter];
		iter++;
	}
	ret[iter] = 0;
	return (ret);
}

/// @brief	create a new node in our env struct
t_env	*env_new(char *name, char *val, t_list **gc)
{
	t_env	*new;

	new = gc_malloc(sizeof(t_env), gc);
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->name = name;
	new->val = val;
	return (new);
}

/// @brief	add a new node to the end of the env struct
void	env_add_back(t_env **env, t_env *new)
{
	t_env	*node;

	if (!new)
		return ;
	if (!(*env))
	{
		*env = new;
		return ;
	}
	node = *env;
	while (node->next)
		node = node->next;
	node->next = new;
}
