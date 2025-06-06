#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int wait_pids(pid_t *pids, int cmd_count) {
  int status;
  int i;
  i = 0;
  while (i < cmd_count) {
    int wstatus;
    waitpid(pids[i], &wstatus, 0);
    if (i == cmd_count - 1) {
      if (WIFEXITED(wstatus))
        status = WEXITSTATUS(wstatus);
      else
        status = 1;
    }
    i++;
  }
  return status;
}
