#include "testdata.h"

// Quote and environment variable handling

t_testdata echo_env_home(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "$HOME", .type = TOKEN_DOUBLE_QUOTED_WORD};
  static t_list token_list2 = {.content = (void *)&token2, .next = NULL};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"echo", "$HOME", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo \"$HOME\"",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata echo_no_expand_home(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "$HOME", .type = TOKEN_SINGLE_QUOTED_WORD};
  static t_list token_list2 = {.content = (void *)&token2, .next = NULL};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"echo", "$HOME", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,

      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo '$HOME'",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata echo_concat_user(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "hello'$USER'world", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list2 = {.content = (void *)&token2, .next = NULL};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"echo", "hello'$USER'world", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};

  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo hello'$USER'world",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata export_and_echo(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "export", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "VAR=test", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token3 = {.value = ";", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token4 = {.value = "echo", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = "$VAR", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list5 = {.content = (void *)&token5, .next = NULL};
  static t_list token_list4 = {.content = (void *)&token4, .next = &token_list5};
  static t_list token_list3 = {.content = (void *)&token3, .next = &token_list4};
  static t_list token_list2 = {.content = (void *)&token2, .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv1[] = {"export", "VAR=test", NULL};
  static char *argv2[] = {"echo", "$VAR", NULL};
  static t_command cmd1 = {
      .type = CMD_SIMPLE,

      .u.simple = {.token_list = NULL, .argv = argv1, .argc = 2}};
  static t_command cmd2 = {
      .type = CMD_SIMPLE,

      .u.simple = {.token_list = NULL, .argv = argv2, .argc = 2}};

  static t_list cmd_list1 = {.content = (void *)&cmd1, .next = NULL};
  static t_list cmd_list2 = {.content = (void *)&cmd2, .next = NULL};
  static t_pipeline pipeline1 = {.command_list = &cmd_list1};
  static t_pipeline pipeline2 = {.command_list = &cmd_list2};
  static t_and_or and_or1 = {
      .pipeline = &pipeline1,
      .op_next = OP_NONE,
  };
  static t_and_or and_or2 = {
      .pipeline = &pipeline2,
      .op_next = OP_NONE,
  };
  static t_ast list2 = {.content = (void *)&and_or2, .next = NULL};
  static t_ast list1 = {.content = (void *)&and_or1, .next = &list2};
  return (t_testdata){
      .input = "export VAR=test ; echo $VAR", .token_list = token_list1, .ast = list1};
}

t_testdata echo_status(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "$?", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list2 = {.content = (void *)&token2, .next = NULL};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"echo", "$?", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,

      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){
      .input = "echo $?", .token_list = token_list1, .ast = ast, .output_file = NULL};
}
