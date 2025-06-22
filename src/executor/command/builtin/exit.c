#include "ast.h"
#include "exit_status.h"
#include "libft.h"
#include "utils/ms_stdio.h"
#include "utils/ms_string.h"

void *check_is_all_digit(unsigned int i, char c, void *acc) {
  (void)i;
  bool *is_valid;
  is_valid = (bool *)acc;
  if (is_valid == false)
    return false;
  *is_valid = ft_isdigit(c);
  return acc;
}
bool check_valid_ascii(char *s) {
  bool is_valid;
  is_valid = true;
  if (*s == '-' || *s == '+')
    s++;
  ms_strreduce(s, &is_valid, check_is_all_digit);
  return is_valid;
}

int exec_exit(t_command *cmd, char **envp) {
  (void)envp;
  if (cmd->type != CMD_SIMPLE) {
    ms_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }
  if (cmd->u.simple.argc == 1)
    exit(EXIT_OK);
  if (cmd->u.simple.argc > 2) {
    ms_fputs("exit: expected less than 1 argument", STDERR_FILENO);
    return EXIT_USER_ERR;
  }
  if (!check_valid_ascii(cmd->u.simple.argv[1])) {
    ms_fputs("exit: expected only 1 + or - and numeric argument",
             STDERR_FILENO);
    return EXIT_USER_ERR;
  }
  exit(ft_atoi(cmd->u.simple.argv[1]));
}
