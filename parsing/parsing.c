/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:26:52 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/30 10:52:01 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*parsing(char *line, t_env *env, t_list **gc, t_ms *ms)
{
	t_parsing	*data;
	t_token		*tokens;

	if (ft_strlen(line) == 0)
		return (NULL);
	if (is_line_valid(line) == 0)
		return (error_line(line, gc), NULL);
	data = replace_var_line(line, env, gc);
	if (!data)
		return (error_line(data->replaced, gc), NULL);
	tokens = tokenise_new_line(data->replaced, gc, ms);
	gc_free(data->replaced, gc);
	gc_free(data, gc);
	if (!tokens)
		return (error_tokens(tokens, gc), NULL);
	if (determine_type(tokens) == 1)
		return (error_tokens(tokens, gc), NULL);
	return (tokens);
}
