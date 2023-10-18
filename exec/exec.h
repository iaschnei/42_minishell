/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostes <acostes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:32:22 by iaschnei          #+#    #+#             */
/*   Updated: 2023/06/13 10:19:53 by acostes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# include <signal.h>
# include "../ms_struct.h"
# include "../minishell.h"
# define EXEC_H
# define READ_END 0
# define WRITE_END 1
# define BOTH_ENDS 2

// -------- QUIT
void	quit_shell(unsigned char errcode, t_ms *ms, int exit_msg);
void	enomem_quit(t_ms *ms);
int		com_not_found(char *arg, t_ms *ms);
int		no_such_file(char *arg, t_ms *ms);

// -------- SIGNALS
void	handle_signals(void);
void	ignore_signals(void);
void	heredoc_handle_signals(void);

// -------- ENV LIST UTILS
int		env_size(t_env *env);
t_env	*env_last(t_env *env);
void	env_delone(t_env *env, t_ms *ms);
void	env_var_delete(t_env *var, t_env **env, t_ms *ms);

// -------- PIPE LIST UTILS
t_pipe	*pipe_new(int index, t_list **gc);
void	pipe_add_back(t_pipe **pipe, t_pipe *new);

// -------- PIPES
size_t	count_pipes(t_token *tokens);
t_pipe	*initialize_pipes(t_token *tokens, t_ms *ms);
void	close_unused_pipe_fds(t_pipe *pipes, int *fd_1, int *fd_2, t_ms *ms);

// -------- ENV EXEC
t_env	*find_in_env(char *name, t_env *env);
char	*initialize_pwd(t_env **env, t_ms *ms);
char	*get_env_var_val(char *name, t_env *env);
char	*set_env_var_val(char *name, char *new_val, t_ms *ms);
char	*parse_env_var_name(char *var, t_ms *ms);
char	*export_env_var(char *var, t_ms *ms);
void	env_var_print(t_env *env, int declare, t_ms *ms);
void	sort_env_tab(t_env *env_tab, size_t tab_len);
void	env_sorted_print(t_env *env, t_ms *ms);
void	set_sh_level(t_ms *ms);

// -------- BUILTINS
void	ms_echo(t_token *token, t_ms *ms);
int		ms_exit(t_token *token, t_ms *ms);
void	ms_export(t_token *token, int is_forked, t_ms *ms);
void	ms_env(t_token *token, t_env *env, t_ms *ms);
void	ms_unset(t_token *token, t_ms *ms);
void	ms_pwd(t_ms *ms);
int		ms_cd(t_token *token, t_ms *ms);
void	print_if_possible(int fd, char *s, char *cmd_name, t_ms *ms);
void	ms_builtin(t_token *token, int is_forked, t_ms *ms);
int		must_be_forked(t_token *token);
int		is_builtin(t_token *token);

// -------- PROCESS
pid_t	*initialise_pids(t_token *tokens, t_ms *ms);
pid_t	protected_fork(t_ms *ms);
pid_t	waitpid_and_set_exit_status(pid_t pid);
void	wait_all_pids(t_ms *ms);

// -------- REDIR
int		open_close(char *path, int oflag, t_ms *ms);
int		check_files(t_token *tokens, t_ms *ms);
char	*check_and_create_files(t_token *tok, t_ms *ms);
int		get_redir_in_fd(t_token *tokens, int pipe_fd, t_ms *ms);
int		get_redir_out_fd(t_token *tokens, int pipe_fd);
void	set_redirs(t_token *tok, t_pipe *pipe_in, t_pipe *pipe_out, t_ms *ms);

// -------- SUBCOMMANDS
int		has_cmd(t_token *token);
void	first_subcommand(t_pipe *pipe, int to_execute, t_ms *ms);
void	intermediate_subcommand(t_pipe *pipe, int to_execute, t_ms *ms);
void	last_subcommand(t_pipe *pipe, int to_execute, t_ms *ms);

// -------- EXEC
t_token	*next_arg(t_token *token);
void	exec_line(t_ms *ms);
void	exec_pipeline(t_ms *ms, t_pipe *pipes);
void	exec_command(t_token *token, int is_single_command, t_ms *ms);
void	exec_builtin_or_program(t_token *token, int is_forked, t_ms *ms);
int		exec_program(t_token *tok, t_ms *ms);
char	**assemble_args(int index, t_token *tokens, t_ms *ms);
char	**env_tab_create(t_env *env, t_ms *ms);
char	*env_join(char *name, char *val, t_ms *ms);
int		exe_from_path(char **args, char **env_tab, int use_fork, t_ms *ms);
char	*get_command_path(char *arg, char *path_var, t_ms *ms);
char	*join_path(char *path, char *command, t_list **gc);
void	single_subcommand(t_token *tok, t_ms *ms);
t_token	*next_arg(t_token *token);
t_token	*next_command(t_token *tok);
void	empty_mem(t_ms *ms);

// -------- MAIN
void	ms_init(t_ms *ms);

// -------- HEREDOC
void	heredoc(t_ms *ms, t_token *tokens);
void	add_to_memory_heredoc(t_ms *ms, char *keyword);
char	*read_heredoc_prompt(t_ms *ms, char *line, char *keyword);
int		write_heredoc_to_pipe(t_token *heredoc, t_ms *ms);
int		get_heredoc_num(t_token *tokens, int max_index);

// ------- REDIR
int		get_redir_in_fd(t_token *tokens, int pipe_fd, t_ms *ms);
int		get_redir_out_fd(t_token *tokens, int pipe_fd);

#endif
