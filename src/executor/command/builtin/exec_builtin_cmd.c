#include <stdbool.h>
#include <unistd.h>
#include "ast.h"
#include "utils/ms_string.h"
#include "executor/command/command.h"
#include "executor/executor.h"
#include "buildin.h"

static bool is_builtin(t_command *cmd);
static const t_builtin_entry *find_builtin(const char *name);
static const t_builtin_entry *get_builtin_table(void);

// TODO: how to manage status of builtin command
// parent
/*
 * Return whether buitin is executed or not
 */
bool exec_builtin_cmd(t_command *cmd) {
  int old_in;
  int old_out;
  const t_builtin_entry *entry;
  if (!is_builtin(cmd))
    return false;
  old_in = dup(STDIN_FILENO);
  old_out = dup(STDOUT_FILENO);
  process_redir_list(cmd->redir_list);
  entry = find_builtin(cmd->u.simple.argv[0]);
  if (entry && entry->func)
    entry->func(cmd);

  dup2(old_in, STDIN_FILENO);
  close(old_in);
  dup2(old_out, STDOUT_FILENO);
  close(old_out);
  return true;
}

static bool is_builtin(t_command *cmd) {
  if (cmd->type != CMD_SIMPLE)
    return false;
  return find_builtin(cmd->u.simple.argv[0]) != NULL;
}

static const t_builtin_entry *find_builtin(const char *name) {
  const t_builtin_entry *table = get_builtin_table();
  for (int i = 0; table[i].name != NULL; i++) {
    if (ms_strcmp(table[i].name, name) == 0)
      return &table[i];
  }
  return NULL;
}

static const t_builtin_entry *get_builtin_table(void) {
  static const t_builtin_entry table[8] = {
      /* {"cd", cd}, */
      /* {"echo",  builtin_echo}, */
      /* {"env",   builtin_env}, */
      /* {"exit",  builtin_exit}, */
      /* {"export",builtin_export}, */
      {"pwd", exec_pwd},
      /* {"unset", builtin_unset}, */
      {NULL, NULL} // 終端
  };
  return table;
}
