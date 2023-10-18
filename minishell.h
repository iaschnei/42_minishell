/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:33:03 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/25 10:29:34 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_struct.h"
# include "utils/utils.h"
# include "parsing/parsing.h"
# include "exec/exec.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line_bonus.h"

# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_errnum;

#endif
