#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"

t_testdata pwd(void) {
  // TOKEN LIST
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("pwd", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "pwd");

  return (t_testdata){.input = "pwd",
                      .token_list =
                          gen_token_list(1, TOKEN_UNQUOTED_WORD, "pwd"),
                      .ast = ast_ptr};
}
