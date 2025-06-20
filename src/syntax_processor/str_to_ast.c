#include "ast.h"
#include "syntax_processor.h"
#include "exit_status.h"
#include "error.h"
#include "token.h"

int str_to_ast(char *input_str, t_ast **ast_ptr) {
  int exit_code;
  t_list *token_list;
  exit_code = EXIT_OK;
  token_list = NULL;
  exit_code = str_to_token(input_str, &token_list);
  if (exit_code != EXIT_OK || token_list == NULL) {
    dev_error();
    return exit_code;
  }
  exit_code = token_to_ast(token_list, ast_ptr);
  lstclear_token(&token_list);
  if (exit_code != EXIT_OK || *ast_ptr == NULL) {
    dev_error();
    return exit_code;
  }
  return exit_code;
}
