#include "ast.h"
#include "exit_status.h"
#include "utils/ms_stdio.h"

int exec_env(t_command *cmd, char **envp) {
  int i;
  if (cmd->type != CMD_SIMPLE) {
    ms_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }
  if (cmd->u.simple.argc != 1) {
    ms_fputs("env: expected no arguments and no options", STDERR_FILENO);
    return EXIT_USER_ERR;
  }
  i = 0;
  while (envp[i]) {
    ms_puts(envp[i]);
    i++;
  }
  return (EXIT_OK);
}
