#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "executor/executor.h"
#include "ast.h"

static pid_t spawn_command(t_command *cmd, int in_fd, int out_fd);
static int is_last_cmd(int i, int cmd_count) { return !(i < cmd_count - 1); }

int run_pipes(pid_t *pids, t_pipeline *pipeline) {
  int input_fd;
  int status;
  int i;
  input_fd = -1;
  status = 0;
  i = 0;
  while (i < pipeline->cmd_count) {
    int pipe_fd[2];
    int output_fd = STDOUT_FILENO;
    if (!is_last_cmd(i, pipeline->cmd_count)) {
      if (pipe(pipe_fd) < 0)
        return EXIT_FAILURE;
      output_fd = pipe_fd[1];
    }
    // TODO: if cd, pwd, export or any other commands that should be executed in
    // parent
    pids[i] =
        spawn_command(&pipeline->commands[i],
                      input_fd == STDIN_FILENO ? -1 : input_fd, output_fd);
    if (input_fd != -1)
      close(input_fd);
    if (is_last_cmd(i, pipeline->cmd_count))
      input_fd = -1;
    else {
      close(pipe_fd[1]);
      input_fd = pipe_fd[0];
    }
    i++;
  }
  return (EXIT_SUCCESS);
}

//
//
static pid_t spawn_command(t_command *cmd, int in_fd, int out_fd) {
  pid_t pid = fork();
  if (pid != 0)
    return pid;

  if (in_fd != STDIN_FILENO) {
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
  }
  if (out_fd != STDOUT_FILENO) {
    dup2(out_fd, STDOUT_FILENO);
    close(out_fd);
  }
  run_command(cmd);
  _exit(1);
}
