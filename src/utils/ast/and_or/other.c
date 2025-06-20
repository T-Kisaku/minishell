#include <stddef.h>
#include "libft.h"
#include "ast.h"

t_and_or *lstget_and_or(t_list *node) {
  if (!node || !node->content)
    return (NULL);
  return ((t_and_or *)node->content);
}
