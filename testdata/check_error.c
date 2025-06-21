#include "error.h"
#include "error.h"
#include <stdio.h>
void check_error(t_error *error) {
  if (!is_error(error))
    return;
  puts("== ERROR ====");
  puts(error->msg);
  del_error(error);
}
