/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:26:53 by acostes           #+#    #+#             */
/*   Updated: 2023/06/01 09:30:40 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H
# include "libft/libft.h"
# include "minishell.h"

enum e_type
{
	NOTHING,
	PIPE,
	R_IN,
	R_OUT,
	R_OUT_APP,
	DELIM,
	CMD,
	ARG,
	FILENAME
};

typedef struct s_parsing
{
	char	*original;
	char	*replaced;
	char	*var;
	int		original_iter;
	int		replaced_iter;
	int		var_len;
}				t_parsing;

typedef struct s_token
{
	char			*text;
	enum e_type		type;
	int				index;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}				t_env;

typedef struct s_ms
{
	t_list	*gc;
	char	*line;
	t_env	*env;
	t_token	*tokens;
	t_token	*heredoc;
	t_token	*head;
	pid_t	*pids;
	int		pid_iter;
	int		heredoc_num;
	int		stdin_save;
	int		has_redir_in;
}	t_ms;

typedef struct s_pipe
{
	int				fd[2];
	int				index;
	struct s_pipe	*next;
}				t_pipe;

#endif
