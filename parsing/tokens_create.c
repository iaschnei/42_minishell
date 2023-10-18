/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:30:54 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/30 10:57:28 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief 	Transform the line into a list of tokens
t_token	*tokenise_new_line(char *line, t_list **gc, t_ms *ms)
{
	t_token	*ret;
	int		iter;
	char	*token;
	int		index;

	ret = NULL;
	iter = 0;
	index = 0;
	while (iter < (int)ft_strlen(line))
	{
		while (line[iter] && (line[iter] == ' ' || line[iter] == '\t'))
			iter++;
		if (!line[iter])
			break ;
		token = extract_token(line, iter, gc);
		if (!token)
			return (NULL);
		iter += ft_strlen(token);
		token = substract_quotes_from_token(token, gc, ms);
		if (!token)
			return (NULL);
		token_add_back(&ret, token_new(token, index, gc));
		index++;
	}
	return (ret);
}

/// @brief  Extract the token (char *) from the line
char	*extract_token(char *line, int iter, t_list **gc)
{
	char	*token;
	int		token_len;
	int		token_iter;
	int		token_end;

	token_iter = 0;
	token_end = find_separator(line, iter);
	token_len = token_end - iter;
	token = (char *)gc_malloc((token_len + 1) * sizeof(char), gc);
	if (!token)
		return (NULL);
	while (iter < token_end)
	{
		token[token_iter] = line[iter];
		token_iter++;
		iter++;
	}
	token[token_iter] = 0;
	return (token);
}

/// @brief 	Find the next separator, or end quote if we're in quotes
/// @return Index of separator
int	find_separator(char *line, int iter)
{
	char	mem;
	int		ret;

	mem = line[iter];
	ret = 0;
	if (mem == '|' || (mem == '<' && line[iter + 1] != '<')
		|| (mem == '>' && line[iter + 1] != '>'))
		return (iter + 1);
	if ((mem == '<' && line[iter + 1] == '<')
		|| (mem == '>' && line[iter + 1] == '>'))
		return (iter + 2);
	while (line[iter + ret] && (line[iter + ret] != ' '
			&& line[iter + ret] != '|'
			&& line[iter + ret] != '>' && line[iter + ret] != '<'))
	{
		if (line[iter + ret] == '"' || line[iter + ret] == '\'')
		{
			mem = line[iter + ret];
			iter++;
			while (line[iter + ret] && line[iter + ret] != mem)
				ret++;
		}
		ret++;
	}
	return (ret + iter);
}

/// @brief 	Removes beginning and closing quotes from the token,
///			effectively allocating a new char *
char	*substract_quotes_from_token(char *token, t_list **gc, t_ms *ms)
{
	char	*new;
	size_t	iter;
	size_t	tok_iter;

	iter = 0;
	tok_iter = 0;
	if (are_there_quotes(token) == 0 || ft_strlen(token) == 0)
		return (token);
	new = gc_malloc((ft_strlen(token) - 2 + 1) * sizeof(char), gc);
	if (!new)
		enomem_quit(ms);
	new = create_new_text(new, token, iter, tok_iter);
	return (new);
}

char	*create_new_text(char *new, char *token, size_t iter, size_t tok_iter)
{
	char	mem;

	while (token[tok_iter + iter])
	{
		while (token[tok_iter + iter] != '"' && token[tok_iter + iter] != '\''
			&& token[tok_iter + iter])
		{
			new[iter] = token[tok_iter + iter];
			iter++;
		}
		mem = token[tok_iter + iter];
		tok_iter++;
		while (token[tok_iter + iter] != mem && token[tok_iter + iter])
		{
			new[iter] = token[tok_iter + iter];
			iter++;
		}
		tok_iter++;
	}
	new[iter] = 0;
	return (new);
}
