#ifndef BUILDIN
#define BUILDIN

#include "ast.h"

typedef void (*builtin_func)(t_command *);

typedef struct s_builtin_entry {
  const char *name;
  builtin_func func;
} t_builtin_entry;

void cd(t_command *cmd);

#endif // !BUILDIN
