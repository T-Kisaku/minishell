#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "ast.h"
#include "executor/pipeline.h"

int exec_pipeline(t_pipeline *pipeline) {
  int status;
  pid_t *pids;
  int cmd_count;
  status = EXIT_OK;
  cmd_count = ft_lstsize(pipeline->command_list);
  pids = ft_calloc(cmd_count + 1, sizeof(pid_t));
  if (!pids) {
    perror(ERR_MSG_MALLOC);
    return EXIT_INTERNAL_ERR;
  }
  exec_cmd_list(pids, pipeline->command_list);
  status = wait_pids(pids, cmd_count);
  free(pids);
  return status;
}