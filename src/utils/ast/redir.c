#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "ast.h"

t_redir *new_redir() {
  t_redir *redir;
  redir = malloc(sizeof(t_redir));
  if (!redir)
    return (NULL);
  redir->type = -1;

  redir->to.is_direct_to_fd = false;
  redir->to.fd = -1;
  redir->to.filename = NULL;
  redir->to.filename_token = NULL;

  redir->from.is_direct_to_fd = false;
  redir->from.fd = -1;
  redir->from.filename = NULL;
  redir->from.filename_token = NULL;
  return redir;
}

t_redir *lstget_redir(t_list *node) {
  if (!node || !node->content)
    return (NULL);
  return ((t_redir *)node->content);
}

void del_redir(void *ptr) {
  t_redir *redir;
  redir = (t_redir *)ptr;
  if (!redir)
    return;
  // TODO: free filename_token here
  free(redir->from.filename);
  free(redir->to.filename);
  free(redir);
}
