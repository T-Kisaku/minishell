#include "ast.h"
#include "testdata.h"
#include "token.h"

// Basic command execution

t_testdata ls(void) {
  // TOKEN LIST
  static t_token_content token = {.value = "ls", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list = {.content = (void *)&token, .next = NULL};

  // AST
  static char *argv[] = {"ls", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 1}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){
      .input = "ls", .token_list = token_list, .ast = ast, .output_file = NULL};
}

t_testdata echo_hello(void) {
  static char *argv[] = {"echo", "hello", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo hello",
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata cat_nofile(void) {
  static char *argv[] = {"cat", "nofile", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};

  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "cat nofile",
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}
