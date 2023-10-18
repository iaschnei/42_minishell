/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:29:37 by acostes           #+#    #+#             */
/*   Updated: 2023/05/05 11:19:33 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipe	*pipe_new(int index, t_list **gc)
{
	t_pipe	*new;

	new = gc_malloc(sizeof(t_pipe), gc);
	if (new == NULL)
		return (NULL);
	new->index = index;
	new->next = NULL;
	return (new);
}

void	pipe_add_back(t_pipe **pipe, t_pipe *new)
{
	t_pipe	*node;

	if (!new)
		return ;
	if (!(*pipe))
	{
		*pipe = new;
		return ;
	}
	node = *pipe;
	while (node->next)
		node = node->next;
	node->next = new;
}
