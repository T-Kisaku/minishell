#include "testdata.h"

// Builtin command edge cases
t_testdata pwd(void) {
  // TOKEN LIST
  static t_token_content token = {.value = "pwd", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list = {.content = (void *)&token, .next = NULL};
  static char *argv[] = {"pwd", NULL};
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
      .input = "pwd", .token_list = token_list, .ast = ast, .output_file = NULL};
}

t_testdata cd_noarg(void) {
  // TOKEN LIST
  static t_token_content token = {.value = "cd", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list = {.content = (void *)&token, .next = NULL};
  static char *argv[] = {"cd", NULL};
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
      .input = "cd", .token_list = token_list, .ast = ast, .output_file = NULL};
}

t_testdata cd_non_existing_dir(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "cd", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "non_existing_dir", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list2 = {.content = (void *)&token2, .next = NULL};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"cd", "non_existing_dir", NULL};
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
  return (t_testdata){.input = "cd non_existing_dir",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata export_two_vars(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "export", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "VAR1=hello", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token3 = {.value = "VAR2=world", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list3 = {.content = (void *)&token3, .next = NULL};
  static t_list token_list2 = {.content = (void *)&token2, .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"export", "VAR1=hello", "VAR2=world", NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv, .argc = 3}};

  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "export VAR1=hello VAR2=world",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata unset_then_echo(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "unset", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "VAR1", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token3 = {.value = ";", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token4 = {.value = "echo", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = "$VAR1", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list5 = {.content = (void *)&token5, .next = NULL};
  static t_list token_list4 = {.content = (void *)&token4, .next = &token_list5};
  static t_list token_list3 = {.content = (void *)&token3, .next = &token_list4};
  static t_list token_list2 = {.content = (void *)&token2, .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv1[] = {"unset", "VAR1", NULL};
  static t_command cmd1 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv1, .argc = 2}};
  static char *argv2[] = {"echo", "$VAR1", NULL};
  static t_command cmd2 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv2, .argc = 2}};

  static t_list command_list1 = {.content = (void *)&cmd1, .next = NULL};
  static t_list command_list2 = {.content = (void *)&cmd2, .next = NULL};
  static t_pipeline pipeline1 = {.command_list = &command_list1};
  static t_pipeline pipeline2 = {.command_list = &command_list2};
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
  return (t_testdata){.input = "unset VAR1 ; echo $VAR1",
                      .token_list = token_list1,
                      .ast = list1,
                      .output_file = NULL};
}

t_testdata exit_status_42(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "exit", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "42", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list2 = {.content = (void *)&token2, .next = NULL};
  static t_list token_list1 = {.content = (void *)&token1, .next = &token_list2};
  static char *argv[] = {"exit", "42", NULL};
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
  return (t_testdata){
      .input = "exit 42", .token_list = token_list1, .ast = ast, .output_file = NULL};
}
