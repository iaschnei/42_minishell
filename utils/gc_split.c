/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:47:46 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/15 11:08:11 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **ret)
{
	int	iter;
	int	j;

	iter = 0;
	while (ret[iter])
		iter++;
	j = 0;
	while (j < iter)
	{
		free(ret[j]);
		j++;
	}
}

static int	words_count(char const *s, char c)
{
	size_t	i;
	int		is_word;
	size_t	count;

	is_word = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (!is_word && s[i] != c)
		{
			is_word = 1;
			count++;
		}
		else if (is_word && s[i] == c)
			is_word = 0;
		i++;
	}
	return (count);
}

static void	get_word(char const *s, size_t word_len, char **tab, size_t tab_idx)
{
	size_t	i;

	i = 0;
	tab[tab_idx] = malloc((word_len + 1) * sizeof(char));
	if (tab[tab_idx] == NULL)
		return ;
	while (i < word_len)
	{
		tab[tab_idx][i] = s[i];
		i++;
	}
	tab[tab_idx][i] = 0;
}

static void	fill_tab(char const *s, char c, char **tab)
{
	size_t	i;
	int		is_word;
	size_t	start;
	size_t	tab_idx;

	i = 0;
	tab_idx = 0;
	is_word = 0;
	while (s[i])
	{
		if (is_word == 0 && s[i] != c)
		{
			is_word = 1;
			start = i;
		}
		if (s[i + 1] == c || s[i + 1] == 0)
		{
			if (is_word == 1)
				get_word(s + start, i - start + 1, tab, tab_idx++);
			is_word = 0;
		}
		i++;
	}
	tab[tab_idx] = NULL;
}

char	**gc_split(char const *s, char c, t_list **gc)
{
	size_t	i;
	char	**tab;
	size_t	nb_words;

	if (!s)
		return (NULL);
	nb_words = words_count(s, c);
	tab = gc_malloc((nb_words + 1) * sizeof(&i), gc);
	if (tab == NULL)
		return (tab);
	fill_tab(s, c, tab);
	i = 0;
	while (tab[i])
		i++;
	if (i != nb_words)
	{
		gc_free_tab(tab, gc);
		tab = NULL;
	}
	return (tab);
}
