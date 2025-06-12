#ifndef BUILDIN
#define BUILDIN

#include "ast.h"

typedef int (*builtin_func)(t_command *);

typedef struct s_builtin_entry {
  const char *name;
  builtin_func func;
} t_builtin_entry;

int cd(t_command *cmd);
int exec_pwd(t_command *cmd);

#endif // !BUILDIN
