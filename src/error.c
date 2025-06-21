#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"

// Return 0 if usr_error succed
int user_error(char *msg) {
  if (write(STDERR_FILENO, msg, ft_strlen(msg)) < 0) {
    perror(ERR_MSG_WRITE);
    return -1;
  }
  return (0);
}

void dev_error() {
  if (write(STDERR_FILENO, ERR_MSG_DEV, ft_strlen(ERR_MSG_DEV)) < 0) {
    perror(ERR_MSG_WRITE);
  }
}

// TODO: think about when malloc is failed
t_error *new_error(int exit_code, const char *msg) {
  t_error *err;
  err = malloc(sizeof(t_error));
  if (!err)
    return NULL;
  err->exit_code = exit_code;
  err->msg = ft_strdup(msg);
  if (!err->msg) {
    free(err);
    return NULL;
  }
  return err;
}
void del_error(t_error *error) {
  if (error != NULL) {
    free(error->msg);
    free(error);
  }
};
ssize_t print_error(const char *msg) {
  ssize_t bytes;

  bytes = write(STDERR_FILENO, msg, ft_strlen(msg));
  if (bytes < 0)
    perror(ERR_MSG_WRITE);
  return bytes;
}

bool is_error(t_error *error) { return error != NULL; }
