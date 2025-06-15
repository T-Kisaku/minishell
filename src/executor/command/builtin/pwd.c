#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "buildin.h"
#include "error.h"
#include "exit_status.h"

int exec_pwd(t_command *cmd) {
  char *cwd;
  if (cmd->type != CMD_SIMPLE) {
    dev_error();
    return (EXIT_INTERNAL_ERR);
  }
  if (cmd->u.simple.argc != 1) {
    user_error("pwd: expected 0 arguments");
    return EXIT_USER_ERR;
  }
  cwd = getcwd(NULL, 0);
  if (cwd == NULL) {
    perror(ERR_MSG_PWD);
    return (EXIT_FAILURE);
  }
  printf("%s\n", cwd);
  free(cwd);
  return (EXIT_OK);
}
