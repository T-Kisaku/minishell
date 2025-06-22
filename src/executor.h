#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <fcntl.h>
#include <stdbool.h>
#include "ast.h"

bool is_builtin(t_command *cmd);
int exec_pipeline(t_pipeline *pipeline, char **envp);
pid_t exec_external_cmd(t_command *cmd, char **envp);
int exec_builtin_cmd(t_command *cmd, char **envp);

#endif // !EXECUTOR_H
