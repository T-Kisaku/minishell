#ifndef BUILTIN
#define BUILTIN

#include "ast.h"

typedef int (*builtin_func)(t_command *, t_list **env_list);

typedef struct s_builtin_entry {
  const char *name;
  builtin_func func;
} t_builtin_entry;

int exec_pwd(t_command *cmd, t_list **env_list);
int exec_env(t_command *cmd, t_list **env_list);
int exec_export(t_command *cmd, t_list **env_list);
int exec_unset(t_command *cmd, t_list **env_list);
int exec_exit(t_command *cmd, t_list **env_list);
int exec_cd(t_command *cmd, t_list **env_list);
int exec_echo(t_command *cmd, t_list **env_list);

#endif // !BUILTIN
