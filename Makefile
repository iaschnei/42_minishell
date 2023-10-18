# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acostes <acostes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 10:43:15 by iaschnei          #+#    #+#              #
#    Updated: 2023/06/13 10:24:33 by acostes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFILES	=	libft/Makefile

SRCS		=	main.c utils/garbage.c utils/gc_libft.c utils/gc_libft_2.c utils/math.c \
				utils/str_utils.c utils/errors.c utils/gc_split.c
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
SRCS_P		=	parsing/env_parsing.c parsing/parsing.c parsing/replace_line_1.c \
				parsing/replace_line_2.c parsing/replace_line_3.c \
				parsing/token_utils.c parsing/tokens_create.c \
				parsing/tokens_type.c parsing/tokens_check.c \
				parsing/parsing_errors.c \
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
SRCS_E		=	exec/builtins.c exec/builtins_cd.c exec/builtins_echo.c \
				exec/builtins_env.c exec/builtins_exit.c exec/builtins_export.c \
				exec/builtins_pwd.c exec/builtins_unset.c \
				exec/quit.c exec/env_exec.c exec/exec.c exec/env_exec_bis.c \
				exec/signals.c exec/env_list_utils.c exec/pipe_list_utils.c \
				exec/heredoc.c exec/path_parse.c exec/pipes.c exec/redir.c \
				exec/subcommands.c exec/process.c exec/move.c \
				exec/redirs_bis.c
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - #
OBJS		=	$(SRCS:.c=.o)

OBJS_P		=	$(SRCS_P:.c=.o)

OBJS_E		=	$(SRCS_E:.c=.o)

CC			=	cc

INCL		=	minishell.h utils/utils.h parsing/parsing.h exec/exec.h \
				libft/libft.h libft/get_next_line_bonus.h libft/ft_printf.h

LIBFT		=	libft/libft.a

FLAGS		=	-Wall -Wextra -Werror

VALG		= 	valgrind --track-fds=yes --trace-children=yes --leak-check=full \
				--suppressions="valgrind_readline_leaks_ignore.supp" \
				--show-leak-kinds=definite,indirect,possible

NAME		=	minishell

COLOR_GREEN	=	\033[1;32m
COLOR_RED	=	\033[1;31m
COLOR_BLUE	=	\033[3;36m
COLOR_PURP	=	\033[1;35m
COLOR_END	=	\033[0m

%.o: %.c
	@$(CC) $(FLAGS) -include minishell.h -g -c $< -o $@
	@echo "$(COLOR_BLUE) || Compiling ($<)...$(COLOR_END)"

all: $(NAME)

$(LIBFT): $(INCL)
	@$(MAKE) -C libft
	@echo "$(COLOR_GREEN) || Compiled libft !$(COLOR_END)"

$(NAME): $(LIBFT) $(OBJS) $(OBJS_E) $(OBJS_P) $(INCL)
	@$(CC) -include minishell.h $(OBJS) $(OBJS_E) $(OBJS_P)\
	 -o $(NAME) libft/libft.a -lreadline
	@echo "$(COLOR_GREEN) || Done !$(COLOR_END)"

vms: $(LIBFT) $(OBJS) $(OBJS_E) $(OBJS_P) $(INCL)
	@echo "$(COLOR_PURP) || Compiling VALGRIND PARSING... !$(COLOR_END)"
	@$(CC) -include minishell.h $(OBJS) $(OBJS_E) $(OBJS_P) -o $(NAME) \
	libft/libft.a  -lreadline && $(VALG) --leak-check=full -s \
	./minishell
	@echo "$(COLOR_GREEN) || Done !$(COLOR_END)"

clean:
	@rm -rf $(OBJS) $(OBJS_E) $(OBJS_P)
	@$(MAKE) -C libft clean
	@echo "$(COLOR_RED) || Cleaning files...$(COLOR_END)"

fclean: clean
	@rm -rf $(NAME) exe
	@$(MAKE) -C libft fclean
	@echo "$(COLOR_RED) || Cleaning library...$(COLOR_END)"

re: fclean all

.PHONY: re fclean all clean parsing exec vexec vparsing
