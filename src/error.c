#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"

// Return 0 if usr_error succed
int usr_error(char *msg) {
  if (write(STDERR_FILENO, msg, ft_strlen(msg)) < 0) {
    perror(ERR_MSG_WRITE);
    return -1;
  }
  return (0);
}
