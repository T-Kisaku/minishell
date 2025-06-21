#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <fcntl.h>
#include <stdbool.h>
#include "ast.h"
#include "error.h"

t_error *exec_pipeline(t_pipeline *pipeline);
pid_t exec_external_cmd(t_command *cmd);
bool exec_builtin_cmd(t_command *cmd);

#endif // !EXECUTOR_H
