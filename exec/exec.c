/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaschnei <iaschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:57:53 by acostes           #+#    #+#             */
/*   Updated: 2023/05/31 10:47:40 by iaschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_line(t_ms *ms)
{
	t_pipe	*pipes;

	if (!ms || !(ms->tokens))
		return ;
	ms->pids = initialise_pids(ms->tokens, ms);
	pipes = initialize_pipes(ms->tokens, ms);
	if (!pipes)
	{
		if (check_files(ms->tokens, ms))
			exec_command(ms->tokens, 1, ms);
	}
	else
		exec_pipeline(ms, pipes);
}

void	exec_pipeline(t_ms *ms, t_pipe *pipes)
{
	if (check_files(ms->tokens, ms) && has_cmd(ms->tokens))
		first_subcommand(pipes, 1, ms);
	ms->tokens = next_command(ms->tokens);
	while (pipes && pipes->next)
	{
		if (check_files(ms->tokens, ms) && has_cmd(ms->tokens))
			intermediate_subcommand(pipes, 1, ms);
		pipes = pipes->next;
		ms->tokens = next_command(ms->tokens);
	}
	if (check_files(ms->tokens, ms) && has_cmd(ms->tokens))
		last_subcommand(pipes, 1, ms);
	wait_all_pids(ms);
}

/// @brief	interprets and executes a command,
///			starting from <token> till it reaches a pipe or the end of line.
///			- if the command is part of a line containing pipes
///				(is_single_command == 0), fork is not made here
///				because it has beem already made before (see subcommands.c).
///			- if the line has no pipes (is_single_command == 1), fork
///				is made if needed (if it's a program, or if it's a builtin which
///				must be forked).
void	exec_command(t_token *token, int is_single_command, t_ms *ms)
{
	int	is_forked;

	is_forked = 0;
	if (!ms || !token)
		return ;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD)
		{
			if (must_be_forked(token) && is_single_command)
			{
				ms->pids[ms->pid_iter] = protected_fork(ms);
				is_forked = 1;
				if (ms->pids[ms->pid_iter] == 0)
					set_redirs(ms->tokens, NULL, NULL, ms);
				else
				{
					waitpid_and_set_exit_status(ms->pids[ms->pid_iter]);
					return ;
				}
			}
			exec_builtin_or_program(token, is_forked, ms);
		}
		token = token->next;
	}
}

void	exec_builtin_or_program(t_token *token, int is_forked, t_ms *ms)
{
	if (is_builtin(token))
		ms_builtin(token, is_forked, ms);
	else
		exec_program(token, ms);
}

int	exec_program(t_token *tok, t_ms *ms)
{
	char	**args;
	char	**env_tab;
	char	*path;
	t_env	*path_var;

	args = assemble_args(tok->index, ms->tokens, ms);
	env_tab = env_tab_create(ms->env, ms);
	if (!args || !env_tab)
		enomem_quit(ms);
	if (access(tok->text, F_OK) != 0 || access(tok->text, X_OK) != 0)
	{
		path_var = find_in_env("PATH", ms->env);
		if (!path_var || (args[0][0] == '.' && args[0][1] == '/'))
			return (no_such_file(args[0], ms));
		path = path_var->val;
		path = get_command_path(args[0], path, ms);
		if (!path)
			return (com_not_found(args[0], ms));
	}
	else
		path = tok->text;
	if (execve(path, args, env_tab) == -1)
		return (com_not_found(args[0], ms));
	gc_free_tab(args, &(ms->gc));
	return (gc_free_tab(env_tab, &(ms->gc)), 0);
}
