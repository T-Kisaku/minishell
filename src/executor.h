#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <fcntl.h>
#include <stdbool.h>
#include "ast.h"

bool is_builtin(t_command *cmd);
int exec_pipeline(t_pipeline *pipeline, t_list **env_list);
char *set_cmd_path(t_command *cmd, t_list *env_list);
pid_t exec_external_cmd(t_command *cmd, t_list *env_list);
int exec_builtin_cmd(t_command *cmd, t_list **env_list);

#endif // !EXECUTOR_H
