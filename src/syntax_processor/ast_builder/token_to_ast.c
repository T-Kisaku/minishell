#include <stdbool.h> //bool,
#include "ast.h"
#include "exit_status.h"
#include "syntax_processor/ast_builder.h"

static int build_ast_from_token_list(t_list **token_list, t_ast **ast_ptr);

int token_to_ast(t_list *token_list, t_ast **ast_ptr) {
  if (!token_list)
    return (EXIT_INTERNAL_ERR);
  *ast_ptr = lstnew_and_or(OP_NONE);
  if (!*ast_ptr)
    return (EXIT_INTERNAL_ERR);
  if (build_ast_from_token_list(&token_list, ast_ptr) != 0) {
    free_ast(ast_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  return (EXIT_OK);
}
static int build_ast_from_token_list(t_list **token_list_ptr, t_ast **ast_ptr) {
  int exit_code;
  while (*token_list_ptr != NULL) {
    exit_code = handle_token_for_ast(token_list_ptr, ast_ptr);
    if (exit_code != EXIT_OK)
      return exit_code;
  }
  return (EXIT_OK);
}
