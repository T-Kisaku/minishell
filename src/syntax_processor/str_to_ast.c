#include "ast.h"
#include "syntax_processor.h"
#include "error.h"
#include "token.h"

t_error *str_to_ast(char *input_str, t_ast **ast_ptr) {
  t_error *error;
  t_list *token_list;
  error = NULL;
  token_list = NULL;
  error = str_to_token(input_str, &token_list);
  if (is_error(error))
    return error;
  error = token_to_ast(token_list, ast_ptr);
  lstclear_token(&token_list);
  if (is_error(error))
    return error;
  return error;
}
