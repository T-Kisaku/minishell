/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 14:32:49 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/pipeline.h"
#include "executor/pipeline/cmd_list.h"
#include "exit_status.h"
#include "ft_list.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

static int loop_cmd_list(t_list *cmd_list, int *pids, t_cmd_fd *cmd_fd,
                         t_list **env_list_ptr);

/**
 * execute list of commands
 * @param pids array of child process id
 * @param cmd_list commands to execute
 * @param env_list env list
 * @return return exit code when last command is builtin, otherwise -1
 */
int exec_cmd_list(pid_t *pids, t_list *cmd_list, t_list **env_list) {
  t_cmd_fd cmd_fd;
  int builtin_exit_code;

  if (!pids || !cmd_list || !env_list)
    return (EXIT_INTERNAL_ERR);
  builtin_exit_code = BUILTIN_NOT_LAST;
  if (init_cmd_fd(&cmd_fd) != 0)
    return (EXIT_INTERNAL_ERR);
  builtin_exit_code = loop_cmd_list(cmd_list, pids, &cmd_fd, env_list);
  return (builtin_exit_code);
}

static int loop_cmd_list(t_list *cmd_list, int *pids, t_cmd_fd *cmd_fd,
                         t_list **env_list_ptr) {
  int builtin_exit_code;
  int result;
  t_command *cmd;
  int cmd_list_size;

  cmd_list_size = ft_lstsize(cmd_list);
  builtin_exit_code = EXIT_OK;
  while (cmd_list) {
    cmd = lstget_command(cmd_list);
    if (create_pipe_if_needed(cmd_fd, cmd_list) != 0) {
      cleanup_pipe_fds(cmd_fd);
      return (EXIT_INTERNAL_ERR);
    }
    set_io_redir(cmd, *cmd_fd);
    result = exec_command(cmd, env_list_ptr, pids, cmd_list_size > 1);
    if (result != BUILTIN_NOT_LAST)
      builtin_exit_code = result;
    cleanup_pipe_fds(cmd_fd);
    cmd_list = cmd_list->next;
  }
  if (cmd_fd->prev_pipe_read >= 0)
    close(cmd_fd->prev_pipe_read);
  return (builtin_exit_code);
}
