/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_line_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:48:59 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/12 15:57:13 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief 	Check if the var exists inside **env
int	does_var_exist(char *var_name, t_env *env)
{
	if (!var_name)
		return (0);
	while (env)
	{
		if (str_isdiff(var_name + 1, env->name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

/// @brief 	Calculate the length of the variable once replaced
int	get_var_replacement_len(char *var_name, t_env *env)
{
	if (!var_name)
		return (0);
	if (ft_strlen(var_name) == 1 && var_name[0] == '$')
		return (1);
	while (env)
	{
		if (str_isdiff(var_name + 1, env->name) == 0)
			return (ft_strlen(env->val));
		env = env->next;
	}
	return (0);
}

/// @brief 	Create the "new line", which takes into account env variables
char	*create_line_replaced(t_parsing *p_data, t_env *env)
{
	int	original_len;

	original_len = ft_strlen(p_data->original);
	while (p_data->original_iter < original_len)
	{
		if (in_single_quote(p_data->original, p_data->original_iter) == 0
			&& p_data->original[p_data->original_iter] == '$'
			&& (ft_isalpha(p_data->original[p_data->original_iter + 1])
				|| p_data->original[p_data->original_iter + 1] == '"'
				|| p_data->original[p_data->original_iter + 1] == '\''))
			var_replacement(p_data, env);
		else if (in_single_quote(p_data->original, p_data->original_iter) == 0
			&& p_data->original[p_data->original_iter] == '$'
			&& p_data->original[p_data->original_iter + 1] == '?')
			dollar_question(p_data);
		else
		{
			p_data->replaced[p_data->replaced_iter]
				= p_data->original[p_data->original_iter];
			p_data->original_iter++;
			p_data->replaced_iter++;
		}
	}
	return (p_data->replaced);
}

/// @brief 	Sub-function that actually does the replacement of vars
void	var_replacement(t_parsing *p_data, t_env *env)
{
	char	*var_name;
	int		iter;

	iter = 0;
	var_name = extract_var_name(p_data->original, p_data->original_iter);
	if (does_var_exist(var_name, env) == 1 || (ft_strlen(var_name) == 1
			&& var_name[0] == '$'))
	{
		p_data->var_len = get_var_replacement_len(var_name, env);
		p_data->var = extract_var(var_name, env);
		if (p_data->var)
		{
			while (iter < p_data->var_len)
			{
				p_data->replaced[p_data->replaced_iter] = p_data->var[iter];
				iter++;
				p_data->replaced_iter++;
			}
		}
		else if (ft_strlen(var_name) == 1 && var_name[0] == '$')
			p_data->replaced[p_data->replaced_iter++] = '$';
	}
	p_data->original_iter += ft_strlen(var_name);
	gc_free(var_name, NULL);
	return ;
}

/// @brief 	extracts the variable from **env
char	*extract_var(char *var_name, t_env *env)
{
	if (!var_name)
		return (NULL);
	while (env)
	{
		if (str_isdiff(var_name + 1, env->name) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
