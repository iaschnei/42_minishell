/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:23:32 by acostes           #+#    #+#             */
/*   Updated: 2023/05/30 10:31:05 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief malloc + store address in garbage collector
/// @return allocated address
void	*gc_malloc(size_t size, t_list **gc)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_lstadd_front(gc, ft_lstnew(ptr));
	return (ptr);
}

/// @brief frees and deletes node <node> in garbage collector list <gc>,
///			reconstructing links between the previous and the next node.
///			if the node to delete is the head of the list,
///			moves the head of the list to the next.
void	gc_node_delete(t_list *node, t_list **gc)
{
	t_list	*prev;

	if (!node || !gc || !(*gc))
		return ;
	if (node == *gc)
	{
		*gc = node->next;
		ft_lstdelone(node, free);
		return ;
	}
	prev = *gc;
	while (prev->next)
	{
		if (prev->next == node)
		{
			prev->next = node->next;
			ft_lstdelone(node, free);
			return ;
		}
		prev = prev->next;
	}
}

/// @brief free (double-free-protected)
///			+ remove address from <gc> if second argument is provided.
void	gc_free(void *ptr, t_list **gc)
{
	t_list	*node;

	if (!ptr)
		return ;
	if (gc)
	{
		node = *gc;
		while (node)
		{
			if (node->content == ptr)
			{
				gc_node_delete(node, gc);
				return ;
			}
			node = node->next;
		}
	}
	else
		free(ptr);
}
