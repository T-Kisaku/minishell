#include <stdio.h>
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
