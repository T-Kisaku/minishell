#ifndef PIPELINE_H
#define PIPELINE_H

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft.h"

void exec_cmd_list(pid_t *pids, t_list *cmd_list);
int wait_pids(pid_t *pids, int cmd_count);

#endif // !PIPELINE_H
