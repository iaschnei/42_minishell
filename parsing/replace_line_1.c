/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_line_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:47:52 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:38:15 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief  Replace the input line taking into account env variables
/// @return The "new" line
t_parsing	*replace_var_line(char *line, t_env *env, t_list **gc)
{
	int			replaced_len;
	t_parsing	*parsing_data;

	parsing_data = gc_malloc(sizeof(t_parsing), gc);
	if (!parsing_data)
		return (NULL);
	replaced_len = get_line_replaced_length(line, env);
	parsing_data->replaced = gc_malloc((replaced_len + 1) * sizeof(char), gc);
	if (!parsing_data->replaced)
		return (NULL);
	parsing_data->replaced[replaced_len] = 0;
	parsing_data->original = line;
	parsing_data->original_iter = 0;
	parsing_data->replaced_iter = 0;
	parsing_data->replaced = create_line_replaced(parsing_data, env);
	if (!parsing_data->replaced)
		return (NULL);
	return (parsing_data);
}

/// @brief  Get the length of the "new" line
int	get_line_replaced_length(char *line, t_env *env)
{
	int	original_len;
	int	return_len;
	int	iter;

	original_len = ft_strlen(line);
	return_len = 0;
	iter = 0;
	while (iter < original_len)
	{
		if (in_single_quote(line, iter) == 0
			&& (line[iter] == '$' && ft_isalpha(line[iter + 1])))
			var_replacement_len(line, &iter, &return_len, env);
		else if (in_single_quote(line, iter) == 0
			&& (line[iter] == '$' && line[iter + 1] == '?'))
		{
			return_len += nbr_len(g_errnum);
			iter += 2;
		}
		else
		{
			iter++;
			return_len++;
		}
	}
	return (return_len);
}

/// @brief 	Get the length of the env variable if it
///         exists and add it to the "new" line len
void	var_replacement_len(char *line, int *iter, int *return_len, t_env *env)
{
	char	*var_name;

	var_name = extract_var_name(line, *iter);
	if (does_var_exist(var_name, env) == 1)
		*return_len += get_var_replacement_len(var_name, env);
	*iter += ft_strlen(var_name);
	gc_free(var_name, NULL);
}

/// @brief 	Extract the variable name from the original line (eg. "$BONJOUR")
char	*extract_var_name(char *line, int iter)
{
	int		len;
	int		temp;
	char	*var_name;

	len = get_var_name_len(line, iter + 1);
	var_name = (char *)malloc((len + 2) * sizeof(char));
	if (!var_name)
		return (NULL);
	temp = 1;
	var_name[0] = line[iter];
	iter++;
	while (ft_isalnum(line[iter]) || line[iter] == '_')
	{
		var_name[temp] = line[iter];
		iter++;
		temp++;
	}
	var_name[temp] = 0;
	return (var_name);
}

/// @brief 	Calculate the length of the variable name (eg: "$OUI" = 4)
int	get_var_name_len(char *line, int iter)
{
	int	return_len;

	return_len = 0;
	while (ft_isalnum(line[iter]) || line[iter] == '_')
	{
		return_len++;
		iter++;
	}
	return (return_len);
}
