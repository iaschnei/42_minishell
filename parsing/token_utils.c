/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:49:31 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:27:38 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_new(char	*content, int index, t_list **gc)
{
	t_token	*new;

	new = gc_malloc(sizeof(t_token), gc);
	if (new == NULL)
		return (NULL);
	new->text = content;
	new->next = NULL;
	new->type = 0;
	new->index = index;
	return (new);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*node;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	node = *lst;
	while (node->next)
		node = node->next;
	node->next = new;
}

void	free_tokens(t_token *tokens, t_list **gc)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		gc_free(tmp, gc);
	}
}
