/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:02:18 by saueda            #+#    #+#             */
/*   Updated: 2025/07/04 17:41:23 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor.h"
#include "executor/command.h"
#include "executor/pipeline.h"
#include "executor/pipeline/cmd_list.h"
#include "exit_status.h"
#include "ft_printf.h"
#include "minishell.h"
#include "ft_printf.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t	spawn_command(t_command *cmd, int *exit_code_ptr,
					t_minishell_state *shell, t_cmd_fd *cmd_fd);
static void		print_command_not_found_error(t_command *cmd);

int	exec_command(t_command *cmd, bool is_in_pipeline, t_minishell_state *shell,
		t_cmd_fd *cmd_fd)
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
	if (is_in_pipeline == false && is_builtin(cmd))
		exit_code = exec_builtin_cmd(cmd, shell);
	else
		set_last_pid(shell->pids, spawn_command(cmd, &exit_code, shell,
				cmd_fd));
	restore_close_io(old_io_fd);
	return (exit_code);
}

static pid_t	spawn_command(t_command *cmd, int *exit_code_ptr,
		t_minishell_state *shell, t_cmd_fd *cmd_fd)
{
	pid_t	pid;

	if (is_builtin(cmd))
	{
		pid = fork();
		if (pid != 0)
			return (pid);
		*exit_code_ptr = exec_builtin_cmd(cmd, shell);
		close_and_int_cmd_fd(cmd_fd);
		del_shell_state(shell);
		exit(*exit_code_ptr);
	}
	else if (set_cmd_path(cmd, shell->env_list) != NULL)
	{
		*exit_code_ptr = BUILTIN_NOT_LAST;
		return (exec_external_cmd(cmd, shell, cmd_fd));
	}
	*exit_code_ptr = BUILTIN_NOT_LAST;
	print_command_not_found_error(cmd);
	*exit_code_ptr = EXIT_NOT_FOUND;
	return (-1);
}

static void	print_command_not_found_error(t_command *cmd)
{
	if (cmd && cmd->type == CMD_SIMPLE && cmd->u.simple.argv[0])
	{
		ft_dprintf(STDERR_FILENO, "command not found: %s\n",
			cmd->u.simple.argv[0]);
	}
}
