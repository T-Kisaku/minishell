#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char **gen_argv(char *first, ...) {
  if (first == NULL) {
    return NULL;
  }

  va_list args1, args2;
  int count = 1;

  // First pass to count arguments
  va_start(args1, first);
  va_copy(args2, args1);

  char *arg = NULL;
  while ((arg = va_arg(args1, char *)) != NULL) {
    count++;
  }
  va_end(args1);

  // Allocate memory for the char* array (+1 for NULL terminator)
  char **argv = malloc((count + 1) * sizeof(char *));
  if (!argv) {
    va_end(args2);
    return NULL;
  }

  // Add first argument
  argv[0] = strdup(first);

  // Add the rest of the arguments
  int i = 1;
  while ((arg = va_arg(args2, char *)) != NULL) {
    argv[i++] = strdup(arg);
  }
  argv[i] = NULL;

  va_end(args2);
  return argv;
}

int gen_argc(char **argv) {
  int count = 0;
  while (argv && argv[count])
    count++;
  return count;
}
