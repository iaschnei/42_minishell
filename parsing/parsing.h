/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:33:57 by iaschnei          #+#    #+#             */
/*   Updated: 2023/05/26 14:44:13 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"
# include "../exec/exec.h"

t_token		*parsing(char *line, t_env *env, t_list **gc, t_ms *ms);
void		error_line(char *line, t_list **gc);
void		error_tokens(t_token *tok, t_list **gc);

// ------- STEP 0: initialise env struct
t_env		*initialise_env(char **env, t_list **gc);
char		*extract_env_var_name(char **env, int var_iter, t_list **gc);
char		*extract_env_var_val(char **env, int var_iter, t_list **gc);
t_env		*env_new(char *name, char *val, t_list **gc);
void		env_add_back(t_env **env, t_env *new);

// ------- STEP 1: replace the line
t_parsing	*replace_var_line(char *line, t_env *env, t_list **gc);
int			get_line_replaced_length(char *line, t_env *env);
void		var_replacement_len(char *line, int *iter, int *return_len,
				t_env *env);
char		*extract_var_name(char *line, int iter);
int			get_var_name_len(char *line, int iter);
int			does_var_exist(char *var_name, t_env *env);
int			get_var_replacement_len(char *var_name, t_env *env);
char		*create_line_replaced(t_parsing *p_data, t_env *env);
void		var_replacement(t_parsing *p_data, t_env *env);
char		*extract_var(char *var_name, t_env *env);
int			is_line_valid(char *line);
int			find_end_quote(char *line, int iter);
int			in_single_quote(char *line, int iter);
void		dollar_question(t_parsing *p_data);

// ------- STEP 2: tokenise the different "words"
t_token		*tokenise_new_line(char *line_replaced, t_list **gc, t_ms *ms);
t_token		*token_new(char	*content, int index, t_list **gc);
void		free_tokens(t_token *tokens, t_list **gc);
void		token_add_back(t_token **lst, t_token *new);
char		*extract_token(char *line, int iter, t_list **gc);
int			find_separator(char *line, int iter);
int			increment_iter(char *line, int iter);
char		*substract_quotes_from_token(char *token, t_list **gc, t_ms *ms);
int			determine_type(t_token *tokens);
void		determine_pipes_and_redir(t_token *tok);
char		*determine_filenames(t_token *tok);
char		*determine_filenames_bis(t_token *tok);
void		determine_cmd_and_arg(t_token *tok);
int			incorrect_tokens(t_token *tok);
int			are_there_quotes(char *token);
int			inside_quotes(char *line, int iter);
char		*create_new_text(char *new, char *token, size_t iter,
				size_t tok_iter);

#endif
