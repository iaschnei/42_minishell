/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:24:32 by acostes           #+#    #+#             */
/*   Updated: 2023/06/12 18:13:44 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>
# include "../libft/libft.h"

// -------- STRING UTILS
int				str_isdiff(char *s1, char *s2);
int				ft_strcmp(char *s1, char *s2);
int				has_only_char(char *s, char c);
int				is_arg_num(char *arg);
int				is_char_in_string(char c, char *s);

// -------- MATH UTILS
size_t			min(size_t a, size_t b);
size_t			max(size_t a, size_t b);

// -------- GARBAGE COLLECTOR
void			*gc_malloc(size_t size, t_list **gc);
void			gc_node_delete(t_list *node, t_list **gc);
void			gc_free(void *ptr, t_list **gc);

// -------- GC_LIBFT
char			*gc_substr(char const *s, size_t start, size_t len,
					t_list **gc);
char			*gc_strdup(const char *s, t_list **gc);
void			gc_free_tab(char **tab, t_list **gc);
void			gc_lstclear(t_list **lst, t_list **gc);
t_list			*gc_lstnew(void *content, t_list **gc);
char			**gc_split(char const *s, char c, t_list **gc);
void			free_tab(char **ret);

// -------- ERRORS
unsigned char	print_err(int errcode, int print_ms, char *name, char *msg);
unsigned char	print_err2(int errcode, char *program, char *file, char *msg);
unsigned char	print_err3(int errcode, char *program, char *id, char *msg);
unsigned char	print_err4(int errcode, char *id);
void			print_heredoc_warning(char *keyword);

#endif
