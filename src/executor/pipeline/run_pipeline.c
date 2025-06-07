#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "executor/executor.h"
#include "ast.h"
#include "executor/pipeline/pipeline.h"

int run_pipeline(t_pipeline *pipeline) {
  int status;
  pid_t *pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
  if (!pids)
    return EXIT_FAILURE;
  if (run_pipes(pids, pipeline) == EXIT_FAILURE)
    return EXIT_FAILURE;
  if (wait_pids(pids, pipeline->cmd_count) == EXIT_FAILURE)
    return EXIT_FAILURE;
  free(pids);
  return EXIT_SUCCESS;
}
