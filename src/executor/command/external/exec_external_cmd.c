#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "ast.h"
#include "error.h"
#include "libft.h"
#include "minishell.h"
#include "executor.h"
#include "executor/command.h"
#include "utils/argv.h"
#include "utils/env.h"

// TODO: error handling for execve, when it fails, free all
pid_t exec_external_cmd(t_command *cmd, t_list *env_list) {
  t_error *error;
  char **envp_tmp;
  pid_t pid;
  envp_tmp = NULL;
  error = env_list_to_envp(env_list, &envp_tmp);
  if (is_error(error)) { // TODO: error handling
    del_error(error);
    return -1;
  }
  pid = fork();
  if (pid != 0) {
    free_argv_null(&envp_tmp);
    return pid;
  }
  process_redir_list(cmd->redir_list);
  if (cmd->type == CMD_SIMPLE) {
    execve(cmd->u.simple.argv[0], cmd->u.simple.argv, envp_tmp);
    perror(ERR_MSG_EXECVP);
    free_argv_null(&envp_tmp);
  } else if (cmd->type == CMD_SUBSHELL) {
    // WARN: this is not supported
    exec_ast(cmd->u.subshell.and_or_list, &env_list);
  }
  // TODO: this is forbitten func
  _exit(1);
}
