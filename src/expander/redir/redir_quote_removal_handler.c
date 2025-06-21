#include "ast.h"
#include "expander.h"

t_error *redir_quote_removal_handler(t_redir *target) {
  if (target->type == REDIR_HERE_DOC) // ヒアドクはなにもしない。
    return NULL;
  if (target->redirect_source.filename_token->type == TOKEN_SINGLE_QUOTED_WORD)
    return (NULL); // 外側がシングルクオートの場合もなにもしない
  return quote_remove_core(target->redirect_source.filename_token);
}
