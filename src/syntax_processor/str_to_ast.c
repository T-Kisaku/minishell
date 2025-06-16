#include "ast.h"
#include "syntax_processor.h"
#include "exit_status.h"
#include "error.h"

int str_to_ast(char *input_str, t_ast *ast) {
  int status;
  t_list *token_list;
  status = EXIT_OK;
  status = str_to_token(input_str, &token_list);
  if (status != EXIT_OK || token_list == NULL) {
    dev_error();
    return status;
  }
  status = token_to_ast(&token_list, &ast);
  if (status != EXIT_OK || ast == NULL) {
    dev_error();
    return status;
  }
  return status;
}
