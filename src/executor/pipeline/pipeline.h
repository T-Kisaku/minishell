#ifndef PIPELINE_H
#define PIPELINE_H

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "ast.h"

int run_pipes(pid_t *pids, t_pipeline *pipeline);
int wait_pids(pid_t *pids, int cmd_count);

#endif // !PIPELINE_H
