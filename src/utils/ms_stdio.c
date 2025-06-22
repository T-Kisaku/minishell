#include <unistd.h>
#include "libft.h"

int ms_fputs(const char *s, int fd) {
  ssize_t bytes;
  bytes = 0;

  bytes += write(fd, s, ft_strlen(s));
  bytes += write(fd, "\n", 1);
  return bytes;
}
int ms_puts(const char *s) { return ms_fputs(s, STDOUT_FILENO); }
