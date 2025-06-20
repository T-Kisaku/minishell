#include <stddef.h>
#include <stdlib.h>
#include "ast.h"

t_pipeline *new_pipeline() {
  t_pipeline *new;
  new = malloc(sizeof(t_pipeline));
  if (!new)
    return (NULL);
  new->command_list = NULL;
  return new;
}
