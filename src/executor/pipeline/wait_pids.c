#include "exit_status.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int wait_pids(pid_t *pids, int cmd_count) {
  int last_cmd_status;
  int i;
  last_cmd_status = EXIT_OK;
  i = 0;
  while (i < cmd_count) {
    waitpid(pids[i], &last_cmd_status, 0);
    if (i == cmd_count - 1) {
      if (WIFEXITED(last_cmd_status))
        last_cmd_status = WEXITSTATUS(last_cmd_status);
      else
        last_cmd_status = EXIT_OK;
    }
    i++;
  }
  return last_cmd_status;
}
