/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 17:13:15 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "executor/command.h"
#include "executor/pipeline/cmd_list.h"
#include "exit_status.h"
#include "minishell.h"
#include "signal_handler.h"
#include "utils/argv.h"
#include "utils/env.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	exec(t_command *cmd, char **envp, t_minishell_state *shell);

pid_t	exec_external_cmd(t_command *cmd, t_minishell_state *shell,
		t_cmd_fd *cmd_fd)
{
	t_error	*error;
	char	**envp_tmp;
	pid_t	pid;

	envp_tmp = NULL;
	error = env_list_to_envp(shell->env_list, &envp_tmp);
	if (is_error(error))
	{
		del_error(error);
		return (-1);
	}
	pid = fork();
	if (pid != 0)
	{
		free_argv_null(&envp_tmp);
		return (pid);
	}
	close_and_int_cmd_fd(cmd_fd);
	exec(cmd, envp_tmp, shell);
	del_shell_state(shell);
	exit(EXIT_INTERNAL_ERR);
}

static void	exec(t_command *cmd, char **envp, t_minishell_state *shell)
{
	if (setup_child_signals() != EXIT_SUCCESS)
	{
		free_argv_null(&envp);
		del_shell_state(shell);
		exit(EXIT_INTERNAL_ERR);
	}
	process_redir_list(cmd->redir_list);
	if (cmd->type == CMD_SIMPLE)
	{
		execve(cmd->u.simple.argv[0], cmd->u.simple.argv, envp);
		perror("execve");
		free_argv_null(&envp);
		del_shell_state(shell);
		exit(EXIT_INTERNAL_ERR);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		exec_ast(cmd->u.subshell.and_or_list, shell);
		free_argv_null(&envp);
		exit(EXIT_INTERNAL_ERR);
	}
}
