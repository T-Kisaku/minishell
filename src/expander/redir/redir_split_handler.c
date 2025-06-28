#include "ast.h"
#include "token.h"
#include "ft_string.h"
#include <stdbool.h>
#include "error.h"
#include "exit_status.h"
t_error *redir_split_handler(t_redir *redir);
static bool check_could_not_split(char *value);

t_error *redir_split_handler(t_redir *redir) {
  if (redir->type == REDIR_HERE_DOC)
    return NULL;
  if (redir->redirect_source.filename_token->type == TOKEN_UNQUOTED_WORD) {
    if (check_could_not_split(redir->redirect_source.filename_token->value) !=
        0)
      return new_error(EXIT_INTERNAL_ERR, "could't splited!!");
  }
  return NULL;
}

static bool check_could_not_split(char *value) {
  while (*value) {
    if (ft_isspace(*value))
      return (true); // bashではエラーになる
    value++;
  }
  return (false);
}
