#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "executor.h"
#include "ast.h"
#include "exit_status.h"
#include <stdio.h>
#include "ft_list.h"

#define PIPE_READ 0
#define PIPE_WRITE 1
#define INVALID_FD -1
#define BUILTIN_NOT_LAST -1

typedef struct s_cmd_fd {
  int prev_pipe_read;
  int current_pipe[2];
} t_cmd_fd;

// 前方宣言
static void set_io_redir(t_command *cmd, t_cmd_fd cmd_fd);
static void close_and_init_fd(int *fd);
static int init_cmd_fd(t_cmd_fd *cmd_fd);
static int create_pipe_if_needed(t_cmd_fd *cmd_fd, t_list *cmd_list);
static int execute_single_command(t_command *cmd, t_list **env_list, pid_t *pids, int *pid_i);
static void cleanup_pipe_fds(t_cmd_fd *cmd_fd);
static void print_command_not_found_error(t_command *cmd);

/**
 * execute list of commands
 * @param pids array of child process id
 * @param cmd_list commands to execute
 * @param env_list env list
 * @return return exit code when last command is builtin, otherwise -1
 */
int exec_cmd_list(pid_t *pids, t_list *cmd_list, t_list **env_list) {
  t_cmd_fd cmd_fd;
  int pid_i;
  int builtin_exit_code;

  if (!pids || !cmd_list || !env_list)
    return EXIT_INTERNAL_ERR;
  builtin_exit_code = BUILTIN_NOT_LAST;
  pid_i = 0;
  if (init_cmd_fd(&cmd_fd) != 0)
    return EXIT_INTERNAL_ERR;
  while (cmd_list) {
    t_command *cmd = lstget_command(cmd_list);
    if (create_pipe_if_needed(&cmd_fd, cmd_list) != 0) {
      cleanup_pipe_fds(&cmd_fd);
      return EXIT_INTERNAL_ERR;
    }
    set_io_redir(cmd, cmd_fd);
    int result = execute_single_command(cmd, env_list, pids, &pid_i);
    if (result != BUILTIN_NOT_LAST)
      builtin_exit_code = result;
    cleanup_pipe_fds(&cmd_fd);
    cmd_list = cmd_list->next;
  }
  if (cmd_fd.prev_pipe_read >= 0)
    close(cmd_fd.prev_pipe_read);
  pids[pid_i] = 0; 
  return builtin_exit_code;
}

static int init_cmd_fd(t_cmd_fd *cmd_fd) {
  if (!cmd_fd) {
    return -1;
  }
  
  cmd_fd->prev_pipe_read = INVALID_FD;
  cmd_fd->current_pipe[PIPE_READ] = INVALID_FD;
  cmd_fd->current_pipe[PIPE_WRITE] = INVALID_FD;
  return 0;
}

static int create_pipe_if_needed(t_cmd_fd *cmd_fd, t_list *cmd_list) {
  if (!ft_lst_is_last(cmd_list)) {
    if (pipe(cmd_fd->current_pipe) < 0) {
      // TODO: エラーメッセージの出力
      return -1;
    }
  }
  return 0;
}

static int execute_single_command(t_command *cmd, t_list **env_list, pid_t *pids, int *pid_i) {
  if (!cmd) {
    return EXIT_INTERNAL_ERR;
  }

  if (is_builtin(cmd)) {
    return exec_builtin_cmd(cmd, env_list);
  } else if (set_cmd_path(cmd, *env_list) != NULL) {
    pids[(*pid_i)++] = exec_external_cmd(cmd, *env_list);
    return BUILTIN_NOT_LAST;
  } else {
    print_command_not_found_error(cmd);
    return EXIT_USER_ERR;
  }
}

static void cleanup_pipe_fds(t_cmd_fd *cmd_fd) {
  close_and_init_fd(&cmd_fd->prev_pipe_read);
  close_and_init_fd(&cmd_fd->current_pipe[PIPE_WRITE]);
  
  cmd_fd->prev_pipe_read = cmd_fd->current_pipe[PIPE_READ];
  cmd_fd->current_pipe[PIPE_READ] = INVALID_FD;
}

static void print_command_not_found_error(t_command *cmd) {
  if (cmd && cmd->type == CMD_SIMPLE && cmd->u.simple.argv[0]) {
    printf("command not found: %s\n", cmd->u.simple.argv[0]);
  }
}

static void close_and_init_fd(int *fd) {
  if (fd && *fd >= 0) {
    close(*fd);
    *fd = INVALID_FD;
  }
}

static void set_io_redir(t_command *cmd, t_cmd_fd cmd_fd) {
  t_redir *redir;

  if (!cmd) {
    return;
  }

  if (cmd_fd.current_pipe[PIPE_WRITE] >= 0) {
    redir = new_redir();
    if (redir) {
      redir->type = REDIR_OUTPUT;
      redir->to_be_redirected.fd = STDOUT_FILENO;
      redir->to_be_redirected.is_direct_to_fd = true;
      redir->redirect_source.fd = cmd_fd.current_pipe[PIPE_WRITE];
      redir->redirect_source.is_direct_to_fd = true;
      ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)redir));
    }
  }

  if (cmd_fd.prev_pipe_read >= 0) {
    redir = new_redir();
    if (redir) {
      redir->type = REDIR_INPUT;
      redir->to_be_redirected.fd = STDIN_FILENO;
      redir->to_be_redirected.is_direct_to_fd = true;
      redir->redirect_source.fd = cmd_fd.prev_pipe_read;
      redir->redirect_source.is_direct_to_fd = true;
      ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)redir));
    }
  }
}


