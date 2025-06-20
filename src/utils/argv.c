#include <stdlib.h>
#include <limits.h>

void free_argv(char ***argv, int num) {
  int i;

  if (!argv || !*argv)
    return;
  i = 0;
  if (num == INT_MAX)
    while ((*argv)[i]) {
      free((*argv)[i]);
      (*argv)[i] = NULL;
      i++;
    }
  else {
    while (i < num) {
      free((*argv)[i]);
      (*argv)[i] = NULL;
      i++;
    }
  }
  free(*argv);
  *argv = NULL;
}
