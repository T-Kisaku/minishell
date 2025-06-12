#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "buildin.h"

int exec_pwd(t_command *cmd) {
  char *cwd;
  // TODO: handle error
  if (cmd->type != CMD_SIMPLE)
    return (EXIT_FAILURE);
  // TODO: handle error
  if (cmd->u.simple.argc != 1)
    return (EXIT_FAILURE);
  cwd = getcwd(NULL, 0);
  if (cwd == NULL) {
    perror("pwd");
    return (EXIT_FAILURE);
  }
  printf("%s\n", cwd);
  free(cwd);
  return (EXIT_SUCCESS);
}
