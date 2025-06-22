
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "ast.h"
#include "error.h"
#include "minishell.h"
#include "executor.h"
#include "executor/command.h"

pid_t exec_external_cmd(t_command *cmd, char **envp) {
  pid_t pid;
  pid = fork();
  if (pid != 0)
    return pid;
  process_redir_list(cmd->redir_list);
  if (cmd->type == CMD_SIMPLE) {
    execvp(cmd->u.simple.argv[0], cmd->u.simple.argv);
    perror(ERR_MSG_EXECVP);
  } else if (cmd->type == CMD_SUBSHELL) {
    // WARN: this is not supported
    exec_ast(cmd->u.subshell.and_or_list, envp);
  }
  // TODO: this is forbitten func
  _exit(1);
}
