#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"

// echo
t_testdata echo_no_args(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("echo", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "echo");

  return (t_testdata){.input = "echo",
                      .token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "echo"),
                      .ast = ast_ptr};
}

// echo hello
t_testdata echo_simple_string(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("echo", "hello", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(2, TOKEN_UNQUOTED_WORD, "echo", TOKEN_UNQUOTED_WORD, "hello");

  return (t_testdata){.input = "echo hello",
                      .token_list = gen_token_list(2, TOKEN_UNQUOTED_WORD, "echo", TOKEN_UNQUOTED_WORD, "hello"),
                      .ast = ast_ptr};
}

// echo -n hello
t_testdata echo_with_n_option(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("echo", "-n", "hello", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "echo", TOKEN_UNQUOTED_WORD, "-n", TOKEN_UNQUOTED_WORD, "hello");

  return (t_testdata){.input = "echo -n hello",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "echo", TOKEN_UNQUOTED_WORD, "-n", TOKEN_UNQUOTED_WORD, "hello"),
                      .ast = ast_ptr};
}

// echo -n hello world
t_testdata echo_with_n_option_multiple_words(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("echo", "-n", "hello", "world", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(4, TOKEN_UNQUOTED_WORD, "echo", TOKEN_UNQUOTED_WORD, "-n", TOKEN_UNQUOTED_WORD, "hello", TOKEN_UNQUOTED_WORD, "world");

  return (t_testdata){.input = "echo -n hello world",
                      .token_list = gen_token_list(4, TOKEN_UNQUOTED_WORD, "echo", TOKEN_UNQUOTED_WORD, "-n", TOKEN_UNQUOTED_WORD, "hello", TOKEN_UNQUOTED_WORD, "world"),
                      .ast = ast_ptr};
}

