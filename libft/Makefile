# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 10:44:43 by acostes           #+#    #+#              #
#    Updated: 2023/05/03 11:20:49 by iaschnei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
				ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_substr.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c \
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
				ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
				ft_print_chars.c ft_print_nbrs.c ft_printf.c \
				get_next_line_utils_bonus.c get_next_line_bonus.c

OBJ			=	${SRC:.c=.o}

HEADERS		=	libft.h ft_printf.h get_next_line_bonus.h

NAME		=	libft.a

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

COLOR_GREEN	=	\033[1;32m
COLOR_RED	=	\033[1;31m
COLOR_BLUE	=	\033[3;36m
COLOR_PURP	=	\033[1;35m
COLOR_END	=	\033[0m

.c.o:
			@${CC} ${CFLAGS} -c $< -o $@
			@echo "$(COLOR_BLUE) || Compiling ($<)...$(COLOR_END)"

all:		${NAME}

${NAME}:	${OBJ} ${HEADERS}
			@ar rc ${NAME} ${OBJ}
			@echo "$(COLOR_GREEN) || Done compiling libft($<)...$(COLOR_END)"
			@ranlib ${NAME}

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
