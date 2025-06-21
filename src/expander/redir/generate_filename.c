#include "ast.h"
#include "error.h"
#include "exit_status.h"

t_error *generate_filename_handler(t_redir *target) {
  if (target->type == REDIR_HERE_DOC)
    return (NULL);
  if (target->redirect_source.is_direct_to_fd)
    return (NULL);
  target->redirect_source.filename =
      ft_strdup(target->redirect_source.filename_token->value);
  if (!target->redirect_source.filename)
    return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
  return (NULL);
}
