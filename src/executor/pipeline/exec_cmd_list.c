#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "executor/executor.h"
#include "ast.h"
#include "libft.h"

typedef struct s_cmd_fd {
  int prev_pipe_read;
  int current_pipe[2];
} t_cmd_fd;

#define PIPE_READ 0
#define PIPE_WRITE 1

static int ms_lst_is_last(t_list *lst) { return lst->next == NULL; }
static void set_io_redir(t_command *cmd, t_cmd_fd cmd_fd);

void exec_cmd_list(pid_t *pids, t_list *cmd_list) {
  t_cmd_fd cmd_fd;
  int pid_i;
  cmd_fd.prev_pipe_read = -1;
  cmd_fd.current_pipe[PIPE_READ] = -1;
  cmd_fd.current_pipe[PIPE_WRITE] = -1;
  pid_i = 0;
  while (cmd_list) {
    if (!ms_lst_is_last(cmd_list)) {
      if (pipe(cmd_fd.current_pipe) < 0)
        return;
    }
    set_io_redir(lstget_command(cmd_list), cmd_fd);
    if (!exec_builtin_cmd(lstget_command(cmd_list))) {
      pids[pid_i++] = exec_external_cmd(lstget_command(cmd_list));
    }
    if (cmd_fd.prev_pipe_read >= 0) {
      close(cmd_fd.prev_pipe_read);
      cmd_fd.prev_pipe_read = -1;
    }
    if (cmd_fd.current_pipe[PIPE_WRITE] >= 0) {
      close(cmd_fd.current_pipe[PIPE_WRITE]);
      cmd_fd.current_pipe[PIPE_WRITE] = -1;
    }
    cmd_fd.prev_pipe_read = cmd_fd.current_pipe[PIPE_READ];
    cmd_fd.current_pipe[PIPE_READ] = -1;

    cmd_list = cmd_list->next;
  }
  close(cmd_fd.prev_pipe_read);
  cmd_fd.prev_pipe_read = -1;
  pids[pid_i++] = 0;
}

static void set_io_redir(t_command *cmd, t_cmd_fd cmd_fd) {
  t_redir *new;
  // TODO: error handling
  if (!cmd)
    return;
  if (cmd_fd.current_pipe[PIPE_WRITE] >= 0) {
    new = new_redir();
    if (new) {
      new->type = REDIR_OUTPUT;
      new->to.is_direct_to_fd = true;
      new->to.fd = cmd_fd.current_pipe[PIPE_WRITE];
      new->from.is_direct_to_fd = true;
      new->from.fd = STDOUT_FILENO;
      ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)new));
    } else {
      // TODO: error handling
      return;
    }
    new = NULL;
  }
  if (cmd_fd.prev_pipe_read >= 0) {
    new = new_redir();
    if (new) {
      new->type = REDIR_INPUT;
      new->to.is_direct_to_fd = true;
      new->to.fd = cmd_fd.prev_pipe_read;
      new->from.is_direct_to_fd = true;
      new->from.fd = STDIN_FILENO;
      ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)new));
    } else {
      // TODO: error handling
      return;
    }
  }
}
