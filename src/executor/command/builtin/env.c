#include <stdio.h>
#include "ast.h"
#include "exit_status.h"
#include "libft.h"
#include "utils/ms_stdio.h"
#include "utils/env.h"

static void print_env_etry(void *content);

int exec_env(t_command *cmd, t_list **env_list) {
  if (cmd->type != CMD_SIMPLE) {
    ms_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }
  if (cmd->u.simple.argc != 1) {
    ms_fputs("env: expected no arguments and no options", STDERR_FILENO);
    return EXIT_USER_ERR;
  }
  ft_lstiter(*env_list, print_env_etry);
  return (EXIT_OK);
}
static void print_env_etry(void *content) {
  t_env *env;
  env = (t_env *)content;
  printf("%s=%s\n", env->key, env->value);
}
