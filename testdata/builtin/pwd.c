#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"

t_testdata pwd(void) {
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

t_testdata pwd_with_arg(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("pwd", "arg1", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(2, TOKEN_UNQUOTED_WORD, "pwd", TOKEN_UNQUOTED_WORD, "arg1");

  return (t_testdata){.input = "pwd arg1",
                      .token_list = gen_token_list(2, TOKEN_UNQUOTED_WORD, "pwd", TOKEN_UNQUOTED_WORD, "arg1"),
                      .ast = ast_ptr};
}
