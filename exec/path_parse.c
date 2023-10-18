/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:23:25 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/15 11:06:22 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief	Try to find the right command path from env $PATH
/// @return The command path or NULL if it doesnt exist (command not found)
char	*get_command_path(char *arg, char *path_var, t_ms *ms)
{
	int		iter;
	char	*path;
	char	**path_tab;

	path_tab = gc_split(path_var, ':', &(ms->gc));
	if (!path_tab)
		return (NULL);
	iter = 0;
	while (path_tab[iter])
	{
		path = join_path(path_tab[iter], arg, &(ms->gc));
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		{
			free_tab(path_tab);
			return (path);
		}
		gc_free(path, &(ms->gc));
		iter++;
	}
	free_tab(path_tab);
	return (NULL);
}

/// @brief Joins the command name (ex"ls") with a path ex("/bin/")
/// CHANGED: line 62 from  "while (com[com_iter] != ' ' && com[com_iter])"
char	*join_path(char *path, char *com, t_list **gc)
{
	int		iter;
	int		com_iter;
	char	*ret;

	ret = gc_malloc((ft_strlen(path) + ft_strlen(com) + 2) * sizeof(char), gc);
	if (!ret)
		return (NULL);
	iter = 0;
	while (path[iter])
	{
		ret[iter] = path[iter];
		iter++;
	}
	ret[iter] = '/';
	iter++;
	com_iter = 0;
	while (com[com_iter])
	{
		ret[iter] = com[com_iter];
		iter++;
		com_iter++;
	}
	ret[iter] = 0;
	return (ret);
}

/// @brief Puts all arguments, including the command name, into a char **
char	**assemble_args(int index, t_token *tokens, t_ms *ms)
{
	char	**ret;
	int		iter;
	int		nb_args;
	t_token	*head;

	iter = 0;
	nb_args = 0;
	while (tokens && tokens->index < index)
		tokens = tokens->next;
	head = tokens;
	while (tokens && (tokens->type == ARG || tokens->type == CMD))
	{
		nb_args++;
		tokens = tokens->next;
	}
	ret = gc_malloc((nb_args + 1) * sizeof(char *), &(ms->gc));
	if (!ret)
		return (NULL);
	while (iter < nb_args)
	{
		ret[iter] = head->text;
		head = head->next;
		iter++;
	}
	return (ret[nb_args] = 0, ret);
}

/// @brief Creates a char** containing all variables from env
char	**env_tab_create(t_env *env, t_ms *ms)
{
	char	**ret;
	int		iter;

	iter = 0;
	ret = gc_malloc((env_size(env) + 1) * sizeof(char *), &(ms->gc));
	if (!ret)
		return (NULL);
	ret[env_size(env)] = 0;
	while (env)
	{
		ret[iter] = env_join(env->name, env->val, ms);
		if (!ret[iter])
			return (NULL);
		env = env->next;
		iter++;
	}
	return (ret);
}

/// @brief joins the val and the name of an env value
char	*env_join(char *name, char *val, t_ms *ms)
{
	char	*ret;
	size_t	total_len;
	size_t	iter;

	iter = 0;
	total_len = ft_strlen(name) + ft_strlen(val) + 1;
	ret = gc_malloc((total_len + 1) * sizeof(char), &(ms->gc));
	if (!ret)
		return (NULL);
	ret[total_len] = 0;
	while (iter < ft_strlen(name))
	{
		ret[iter] = name[iter];
		iter++;
	}
	ret[iter++] = '=';
	while (iter < total_len)
	{
		ret[iter] = val[iter - ft_strlen(name) - 1];
		iter++;
	}
	return (ret);
}
