#ifndef BUILTIN
#define BUILTIN

#include "ast.h"

typedef int (*builtin_func)(t_command *, char **envp);

typedef struct s_builtin_entry {
  const char *name;
  builtin_func func;
} t_builtin_entry;

int exec_pwd(t_command *cmd, char **envp);
int exec_env(t_command *cmd, char **envp);
int exec_export(t_command *cmd, char **envp);
int exec_unset(t_command *cmd, char **envp);
int exec_exit(t_command *cmd, char **envp);
int exec_cd(t_command *cmd, char **envp);
int exec_echo(t_command *cmd, char **envp);

#endif // !BUILTIN
