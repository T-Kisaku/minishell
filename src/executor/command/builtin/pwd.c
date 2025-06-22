#include <stdio.h>
#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "utils/ms_stdio.h"

int exec_pwd(t_command *cmd, char **envp) {
  (void)envp;
  char *cwd;
  if (cmd->type != CMD_SIMPLE) {
    ms_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }
  if (cmd->u.simple.argc != 1) {
    ms_fputs("pwd: expected no arguments", STDERR_FILENO);
    return EXIT_USER_ERR;
  }
  cwd = getcwd(NULL, 0);
  if (cwd == NULL) {
    ms_fputs("strerror for cwd bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }

  printf("%s\n", cwd);
  free(cwd);
  return (EXIT_OK);
}
