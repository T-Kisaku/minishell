#ifndef BUILDIN
#define BUILDIN

#include "ast.h"
#include "error.h"

typedef t_error *(*builtin_func)(t_command *);

typedef struct s_builtin_entry {
  const char *name;
  builtin_func func;
} t_builtin_entry;

t_error *cd(t_command *cmd);
t_error *exec_pwd(t_command *cmd);

#endif // !BUILDIN
