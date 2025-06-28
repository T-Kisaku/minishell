#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "ft_stdio.h"

static int print_error(const char *message) {
  ft_fputs(message, STDERR_FILENO);
  return EXIT_USER_ERR;
}

static int print_internal_error(const char *message) {
  ft_fputs(message, STDERR_FILENO);
  return EXIT_INTERNAL_ERR;
}

int exec_pwd(t_command *cmd, t_list **env_list) {
  (void)env_list;
  char *cwd;

  if (cmd->type != CMD_SIMPLE) {
    return print_internal_error("pwd: invalid command type\n");
  }
  if (cmd->u.simple.argc != 1) {
    return print_error("pwd: too many arguments\n");
  }
  cwd = getcwd(NULL, 0);
  if (cwd == NULL) {
    return print_internal_error(
        "pwd: failed to get current working directory\n");
  }
  printf("%s\n", cwd);
  free(cwd);
  return EXIT_OK;
}
