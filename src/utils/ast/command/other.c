#include "ast.h"

t_command *lstget_command(t_list *node) {
  if (!node || !node->content)
    return (NULL);
  return ((t_command *)node->content);
}
