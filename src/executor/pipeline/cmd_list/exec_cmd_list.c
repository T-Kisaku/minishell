/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 12:35:17 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor.h"
#include "executor/command.h"
#include "executor/pipeline.h"
#include "executor/pipeline/cmd_list.h"
#include "exit_status.h"
#include "ft_list.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int	loop_cmd_list(t_list *cmd_list, int *pids, t_cmd_fd *cmd_fd,
				t_list **env_list_ptr);
static int	execute_single_command(t_command *cmd, t_list **env_list,
				pid_t *pids);
static void	print_command_not_found_error(t_command *cmd);

/**
 * execute list of commands
 * @param pids array of child process id
 * @param cmd_list commands to execute
 * @param env_list env list
 * @return return exit code when last command is builtin, otherwise -1
 */
int	exec_cmd_list(pid_t *pids, t_list *cmd_list, t_list **env_list)
{
	t_cmd_fd	cmd_fd;
	int			builtin_exit_code;

	if (!pids || !cmd_list || !env_list)
		return (EXIT_INTERNAL_ERR);
	builtin_exit_code = BUILTIN_NOT_LAST;
	if (init_cmd_fd(&cmd_fd) != 0)
		return (EXIT_INTERNAL_ERR);
	builtin_exit_code = loop_cmd_list(cmd_list, pids, &cmd_fd, env_list);
	if (cmd_fd.prev_pipe_read >= 0)
		close(cmd_fd.prev_pipe_read);
	return (builtin_exit_code);
}

static int	loop_cmd_list(t_list *cmd_list, int *pids, t_cmd_fd *cmd_fd,
		t_list **env_list_ptr)
{
	int			builtin_exit_code;
	int			result;
	t_command	*cmd;

	builtin_exit_code = EXIT_OK;
	while (cmd_list)
	{
		cmd = lstget_command(cmd_list);
		if (create_pipe_if_needed(cmd_fd, cmd_list) != 0)
		{
			cleanup_pipe_fds(cmd_fd);
			return (EXIT_INTERNAL_ERR);
		}
		set_io_redir(cmd, *cmd_fd);
		result = execute_single_command(cmd, env_list_ptr, pids);
		if (result != BUILTIN_NOT_LAST)
			builtin_exit_code = result;
		cleanup_pipe_fds(cmd_fd);
		cmd_list = cmd_list->next;
	}
	return (builtin_exit_code);
}

static int	execute_single_command(t_command *cmd, t_list **env_list,
		pid_t *pids)
{
	int		exit_code;
	t_io_fd	old_io_fd;

	if (!cmd)
		return (EXIT_INTERNAL_ERR);
	dup_io(&old_io_fd);
	exit_code = process_redir_list(cmd->redir_list);
	if (exit_code != 0)
		return (exit_code);
	if (is_builtin(cmd))
		exit_code = (exec_builtin_cmd(cmd, env_list));
	else if (set_cmd_path(cmd, *env_list) != NULL)
	{
		set_last_pid(pids, exec_external_cmd(cmd, *env_list));
		exit_code = (BUILTIN_NOT_LAST);
	}
	else
	{
		print_command_not_found_error(cmd);
		exit_code = (EXIT_USER_ERR);
	}
	restore_close_io(old_io_fd);
	return (exit_code);
}

static void	print_command_not_found_error(t_command *cmd)
{
	if (cmd && cmd->type == CMD_SIMPLE && cmd->u.simple.argv[0])
	{
		printf("command not found: %s\n", cmd->u.simple.argv[0]);
	}
}
