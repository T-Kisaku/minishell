#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "ast.h"

int run_pipeline(t_pipeline *pipeline);
int run_command(t_command *cmd);

#endif // !EXECUTOR_H
