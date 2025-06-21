#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "executor/command/buildin.h"
#include "error.h"
#include "exit_status.h"

t_error *exec_pwd(t_command *cmd) {
  char *cwd;
  if (cmd->type != CMD_SIMPLE)
    return new_error(EXIT_INTERNAL_ERR, "cmd->type should be CMD_SIMPLE bro");
  if (cmd->u.simple.argc != 1)
    return new_error(EXIT_USER_ERR, "pwd: expected 0 arguments");
  cwd = getcwd(NULL, 0);
  if (cwd == NULL)
    return new_error(EXIT_INTERNAL_ERR, "strerror for cwd bro");

  printf("%s\n", cwd);
  free(cwd);
  return NULL;
}
