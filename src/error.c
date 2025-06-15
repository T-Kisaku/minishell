#include <stdio.h>
#include <unistd.h>
#include "error.h"
#include "libft.h"

int internal_err(char *s) {
  perror(s);
  return EXIT_INTERNAL_ERR;
}

int user_err(char *msg) {
  if (write(STDERR_FILENO, msg, ft_strlen(msg)) < 0)
    return internal_err(ERR_MSG_WRITE);
  return EXIT_USER_ERR;
}
