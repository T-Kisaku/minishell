#include "ast.h"
#include "expander.h"

t_error *redir_expand_handler(t_redir *redir, t_list *env_list) {
	(void)env_list; // env_list is not used in this function
  t_error *error;
  error = NULL;
  if (redir->type == REDIR_HERE_DOC) {
    if (redir->redirect_source.filename_token->type == TOKEN_UNQUOTED_WORD) {
      error = expand_single_token(redir->redirect_source.filename_token, env_list);
      if (is_error(error))
        return error;
    }
  } else if (redir->redirect_source.filename_token->type !=
             TOKEN_SINGLE_QUOTED_WORD) {
    error = expand_single_token(redir->redirect_source.filename_token, env_list);
    if (is_error(error))
      return error;
  }
  return NULL;
}
