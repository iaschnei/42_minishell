/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:50:16 by acostes           #+#    #+#             */
/*   Updated: 2023/06/01 09:46:24 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief writes an error message in STDERR_FILENO,
///			sets errnum to errcode and returns it
///			The message printed follows the syntax:
///			"[minishell: ]<name>: <msg>"
///			("minishell: " is printed only if print_ms is True)
/// @return errcode
unsigned char	print_err(int errcode, int print_ms, char *name, char *msg)
{
	char	*to_print;
	char	*to_free;

	g_errnum = errcode;
	to_print = ft_strjoin(name, ": ");
	to_free = to_print;
	to_print = ft_strjoin(to_print, msg);
	gc_free(to_free, NULL);
	to_free = to_print;
	if (print_ms)
	{
		to_print = ft_strjoin("minishell: ", to_print);
		gc_free(to_free, NULL);
		to_free = to_print;
	}
	write(2, to_print, ft_strlen(to_print));
	gc_free(to_free, NULL);
	return (errcode);
}

/// @brief writes an error message in STDERR_FILENO,
///			sets errnum to errcode and returns it
///			The message printed follows the syntax:
///			"minishell: <program>: <file>: <msg>"
/// @return errcode
unsigned char	print_err2(int errcode, char *program, char *file, char *msg)
{
	char	*to_print;
	char	*to_free;

	g_errnum = errcode;
	to_print = ft_strjoin("minishell: ", program);
	to_free = to_print;
	to_print = ft_strjoin(to_print, ": ");
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, file);
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, ": ");
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, msg);
	gc_free(to_free, NULL);
	to_free = to_print;
	write(2, to_print, ft_strlen(to_print));
	gc_free(to_free, NULL);
	return (errcode);
}

/// @brief writes an error message in STDERR_FILENO,
///			sets errnum to errcode and returns it
///			The message printed follows the syntax:
///			"minishell: <program>: `<id>': <msg>"
/// @return errcode
unsigned char	print_err3(int errcode, char *program, char *id, char *msg)
{
	char	*to_print;
	char	*to_free;

	g_errnum = errcode;
	to_print = ft_strjoin("minishell: ", program);
	to_free = to_print;
	to_print = ft_strjoin(to_print, ": `");
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, id);
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, "': ");
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, msg);
	gc_free(to_free, NULL);
	to_free = to_print;
	write(2, to_print, ft_strlen(to_print));
	gc_free(to_free, NULL);
	return (errcode);
}

/// @brief writes an error message in STDERR_FILENO,
///			sets errnum to errcode and returns it
///			The message printed follows the syntax:
///			"minishell: syntax error near unexpected token `<id>'\n"
/// @return errcode
unsigned char	print_err4(int errcode, char *id)
{
	char	*to_print;
	char	*to_free;

	g_errnum = errcode;
	to_print = "minishell: syntax error near unexpected token `";
	to_print = ft_strjoin(to_print, id);
	to_free = to_print;
	to_print = ft_strjoin(to_print, "'\n");
	gc_free(to_free, NULL);
	to_free = to_print;
	write(2, to_print, ft_strlen(to_print));
	gc_free(to_free, NULL);
	return (errcode);
}

/// @brief writes a warning message when heredoc prompt gets a EOF on empty line
void	print_heredoc_warning(char *keyword)
{
	char	*to_print;
	char	*to_free;

	to_print = "minishell: warning: here-document ";
	to_print = ft_strjoin(to_print, "delimited by end-of-file (wanted `");
	to_free = to_print;
	to_print = ft_strjoin(to_print, keyword);
	gc_free(to_free, NULL);
	to_free = to_print;
	to_print = ft_strjoin(to_print, "')\n");
	gc_free(to_free, NULL);
	to_free = to_print;
	write(2, to_print, ft_strlen(to_print));
	gc_free(to_free, NULL);
}
