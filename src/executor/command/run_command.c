
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ast.h"
#include "minishell.h"
#include "command.h"

// TODO: how to get stauts of execvp
int run_command(t_command *cmd) {
  process_redirs(cmd->redirs, cmd->redir_count);
  if (cmd->type == CMD_SIMPLE) {
    execvp(cmd->u.simple.argv[0], cmd->u.simple.argv);
    perror("execvp");
  } else if (cmd->type == CMD_SUBSHELL) {
    exit(EXIT_FAILURE);
    // WARN: not supported
    exec_ast(cmd->u.subshell.list);
  }
  return 1;
}
