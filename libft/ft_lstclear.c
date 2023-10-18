/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:16:23 by acostes           #+#    #+#             */
/*   Updated: 2023/04/25 11:03:56 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !(*lst) || !del)
		return ;
	while ((*lst)->next)
	{
		(*del)((*lst)->content);
		temp = (*lst);
		*lst = (*lst)->next;
		free(temp);
	}
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}
