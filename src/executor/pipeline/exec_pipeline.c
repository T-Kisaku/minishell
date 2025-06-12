#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "ast.h"
#include "executor/pipeline/pipeline.h"

int exec_pipeline(t_pipeline *pipeline) {
  int status;
  pid_t *pids;
  int cmd_count;
  status = EXIT_SUCCESS;
  cmd_count = ft_lstsize(pipeline->command_list);
  // TODO: free allocation properly
  pids = ft_calloc(cmd_count + 1, sizeof(pid_t));
  // TODO: return corresponded error, not EXIT_FAILURE
  if (!pids)
    return EXIT_FAILURE;
  exec_cmd_list(pids, pipeline->command_list);
  status = wait_pids(pids, cmd_count);
  free(pids);
  if (status != EXIT_SUCCESS)
    return status;
  return status;
}
