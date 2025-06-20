#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"

t_testdata ls(void) {
  // TOKEN LIST
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("ls", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "ls");

  return (t_testdata){.input = "ls",
                      .token_list = gen_token_list(1,TOKEN_UNQUOTED_WORD, "ls"),
                      .ast = ast_ptr};
}

t_testdata ls_with_args(void) {
  // TOKEN LIST
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("ls", "-la", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(2, 
                                                   TOKEN_UNQUOTED_WORD, "ls",
                                                   TOKEN_UNQUOTED_WORD, "-la");

  return (t_testdata){.input = "ls -la",
                      .token_list = gen_token_list(2,
                                                   TOKEN_UNQUOTED_WORD, "ls",
                                                   TOKEN_UNQUOTED_WORD, "-la"
                                                   ),
                      .ast = ast_ptr};
}
