/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:37:47 by acostes           #+#    #+#             */
/*   Updated: 2023/05/30 09:57:36 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief calculates the size of a t_env-type linked list
/// @return size of the list
int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

/// @brief returns last element of the env list
/// @return last element of env list
t_env	*env_last(t_env *env)
{
	if (!env)
		return (env);
	while (env->next)
		env = env->next;
	return (env);
}

/// @brief frees and delete <env> node in environment list
void	env_delone(t_env *env, t_ms *ms)
{
	if (!env)
		return ;
	gc_free(env->name, &(ms->gc));
	gc_free(env->val, &(ms->gc));
	gc_free(env, &(ms->gc));
}

/// @brief frees and deletes <var> in environment list <env>,
///			reconstructing links between the previous and the next node.
///			if the node to delete is the head of the list,
///			moves the head of the list to the next.
void	env_var_delete(t_env *var, t_env **env, t_ms *ms)
{
	t_env	*prev;

	if (!var || !env || !(*env))
		return ;
	if (var == *env)
	{
		*env = (*env)->next;
		env_delone(var, ms);
		return ;
	}
	prev = *env;
	while (prev->next)
	{
		if (prev->next == var)
		{
			prev->next = var->next;
			env_delone(var, ms);
			return ;
		}
		prev = prev->next;
	}
}
