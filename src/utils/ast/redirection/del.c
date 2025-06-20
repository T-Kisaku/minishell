#include <stddef.h>
#include "libft.h"
#include "ast.h"

void del_redir(void *ptr) {
  t_redir *redir;
  redir = (t_redir *)ptr;
  if (!redir)
    return;
  // TODO: free filename_token here
  free(redir->redirect_source.filename);
  del_token(redir->redirect_source.filename_token);
  free(redir->to_be_redirected.filename);
  del_token(redir->to_be_redirected.filename_token);
  free(redir);
}

void clear_redir_list(t_list **head) {
  if (!head || !*head)
    return;
  ft_lstclear(head, del_redir);
}
