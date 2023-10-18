/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:42:17 by acostes           #+#    #+#             */
/*   Updated: 2023/05/26 14:23:51 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief same behavior as ft_substr, but with mallocs recorded
///			in garbage collector <gc>
/// @return the created substring
char	*gc_substr(char const *s, size_t start, size_t len, t_list **gc)
{
	char	*substr;
	size_t	initial_len;

	if (!s)
		return (NULL);
	initial_len = ft_strlen(s);
	if (start > initial_len)
	{
		substr = gc_malloc(sizeof(char), gc);
		substr[0] = 0;
		return (substr);
	}
	if (len > initial_len - start)
		len = initial_len - start;
	substr = gc_malloc((len + 1) * sizeof(char), gc);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

/// @brief same behavior as ft_strdup, but with mallocs recorded
///			in garbage collector <gc>
/// @return the created duplicate string
char	*gc_strdup(const char *s, t_list **gc)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s) + 1;
	dup = gc_malloc(size, gc);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, size);
	return (dup);
}

void	gc_free_tab(char **tab, t_list **gc)
{
	int	iter;
	int	j;

	iter = 0;
	while (tab[iter])
		iter++;
	j = 0;
	while (j < iter)
	{
		gc_free(tab[j], gc);
		j++;
	}
	gc_free(tab, gc);
}

void	gc_lstclear(t_list **lst, t_list **gc)
{
	t_list	*temp;

	if (!lst || !(*lst))
		return ;
	while ((*lst)->next)
	{
		gc_free((*lst)->content, gc);
		temp = (*lst);
		*lst = (*lst)->next;
		gc_free(temp, gc);
	}
	gc_free((*lst)->content, gc);
	gc_free(*lst, gc);
	*lst = NULL;
}

t_list	*gc_lstnew(void *content, t_list **gc)
{
	t_list	*head;

	head = gc_malloc(sizeof(t_list), gc);
	if (head == NULL)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}
