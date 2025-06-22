#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "executor.h"
#include "ast.h"
#include "exit_status.h"
#include "libft.h"

typedef struct s_cmd_fd {
  int prev_pipe_read;
  int current_pipe[2];
} t_cmd_fd;

#define PIPE_READ 0
#define PIPE_WRITE 1

static int ms_lst_is_last(t_list *lst) { return lst->next == NULL; }
static void set_io_redir(t_command *cmd, t_cmd_fd cmd_fd);

// - return exit code when last command is builtin
// - return -1 if builtin command is not the last
int exec_cmd_list(pid_t *pids, t_list *cmd_list, char **envp) {
  t_cmd_fd cmd_fd;
  int pid_i;
  int builtin_exit_code;
  builtin_exit_code = -1;
  cmd_fd.prev_pipe_read = -1;
  cmd_fd.current_pipe[PIPE_READ] = -1;
  cmd_fd.current_pipe[PIPE_WRITE] = -1;
  pid_i = 0;
  while (cmd_list) {
    if (!ms_lst_is_last(cmd_list)) {
      if (pipe(cmd_fd.current_pipe) < 0) {
        // TODO: print error for pipe
        return EXIT_INTERNAL_ERR;
      }
    }
    set_io_redir(lstget_command(cmd_list), cmd_fd);
    if (is_builtin(lstget_command(cmd_list)))
      builtin_exit_code = exec_builtin_cmd(lstget_command(cmd_list), envp);
    else {
      pids[pid_i++] = exec_external_cmd(lstget_command(cmd_list));
      builtin_exit_code = -1;
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
  return builtin_exit_code;
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
      new->to_be_redirected.is_direct_to_fd = true;
      new->to_be_redirected.fd = cmd_fd.current_pipe[PIPE_WRITE];
      new->redirect_source.is_direct_to_fd = true;
      new->redirect_source.fd = STDOUT_FILENO;
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
      new->to_be_redirected.is_direct_to_fd = true;
      new->to_be_redirected.fd = cmd_fd.prev_pipe_read;
      new->redirect_source.is_direct_to_fd = true;
      new->redirect_source.fd = STDIN_FILENO;
      ft_lstadd_front(&cmd->redir_list, ft_lstnew((void *)new));
    } else {
      // TODO: error handling
      return;
    }
  }
}
