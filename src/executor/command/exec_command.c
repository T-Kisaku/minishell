/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:02:18 by saueda            #+#    #+#             */
/*   Updated: 2025/07/01 13:56:16 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor.h"
#include "executor/command.h"
#include "executor/pipeline.h"
#include "executor/pipeline/cmd_list.h"
#include "exit_status.h"
#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int	exec_builtin_or_external(t_command *cmd, bool is_in_pipeline,
				t_minishell_state *shell);
static void	print_command_not_found_error(t_command *cmd);

int	exec_command(t_command *cmd, bool is_in_pipeline, t_minishell_state *shell)
{
	int		exit_code;
	t_io_fd	old_io_fd;

	exit_code = BUILTIN_NOT_LAST;
	dup_io(&old_io_fd);
	exit_code = process_redir_list(cmd->redir_list);
	if (exit_code != 0)
	{
		restore_close_io(old_io_fd);
		return (exit_code);
	}
	exec_builtin_or_external(cmd, is_in_pipeline, shell);
	restore_close_io(old_io_fd);
	return (exit_code);
}

static int	exec_builtin_or_external(t_command *cmd, bool is_in_pipeline,
		t_minishell_state *shell)
{
	int	exit_code;
	int	pid;

	exit_code = EXIT_OK;
	if (is_builtin(cmd))
	{
		pid = exec_builtin_cmd(cmd, &exit_code, is_in_pipeline, shell);
		if (exit_code == BUILTIN_NOT_LAST && pid > 0)
			set_last_pid(shell->pids, pid);
	}
	else if (set_cmd_path(cmd, shell->env_list) != NULL)
	{
		set_last_pid(shell->pids, exec_external_cmd(cmd, shell));
		exit_code = (BUILTIN_NOT_LAST);
	}
	else
	{
		print_command_not_found_error(cmd);
		exit_code = (EXIT_USER_ERR);
	}
	return (exit_code);
}

static void	print_command_not_found_error(t_command *cmd)
{
	if (cmd && cmd->type == CMD_SIMPLE && cmd->u.simple.argv[0])
	{
		printf("command not found: %s\n", cmd->u.simple.argv[0]);
	}
}
