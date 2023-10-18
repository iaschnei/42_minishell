/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:27:27 by acostes           #+#    #+#             */
/*   Updated: 2022/11/17 17:45:16 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	if (!f || !del || !lst)
		return (NULL);
	head = ft_lstnew((*f)(lst->content));
	if (head == NULL)
		return (NULL);
	node = head;
	while (lst->next)
	{
		lst = lst->next;
		node->next = ft_lstnew((*f)(lst->content));
		if (node->next == NULL)
			return (NULL);
		node = node->next;
	}
	return (head);
}
