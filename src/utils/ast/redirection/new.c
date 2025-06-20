#include <stddef.h>
#include <stdbool.h>
#include "ast.h"
#include "libft.h"

t_redir *new_redir() {
  t_redir *redir;
  redir = malloc(sizeof(t_redir));
  if (!redir)
    return (NULL);
  redir->type = -1;

  redir->to_be_redirected.is_direct_to_fd = false;
  redir->to_be_redirected.fd = -1;
  redir->to_be_redirected.filename = NULL;
  redir->to_be_redirected.filename_token = NULL;

  redir->redirect_source.is_direct_to_fd = false;
  redir->redirect_source.fd = -1;
  redir->redirect_source.filename = NULL;
  redir->redirect_source.filename_token = NULL;
  return redir;
}

t_list *lstnew_redir(t_redir_type redir_type, t_token *filename_token) {
  t_redir *new;
  new = new_redir();
  if (!new)
    return NULL;

  new->type = redir_type;
  new->redirect_source.filename_token = filename_token;
  new->to_be_redirected.is_direct_to_fd = true;
  if (redir_type == REDIR_INPUT || redir_type == REDIR_HERE_DOC)
    new->to_be_redirected.fd = STDIN_FILENO;
  else if (redir_type == REDIR_OUTPUT || redir_type == REDIR_APPEND)
    new->to_be_redirected.fd = STDOUT_FILENO;
  else
    return NULL;

  return ft_lstnew((void *)new);
}
t_list *lstadd_back_redir(t_list **redir_list_ptr, t_redir_type redir_type,
                          t_token *filename_token) {
  t_list *new_list;
  new_list = lstnew_redir(redir_type, filename_token);
  ft_lstadd_back(redir_list_ptr, new_list);
  return new_list;
}
