#include "testdata.h"

// Pipe related commands

t_testdata ls_pipe_grep(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "ls", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "|", .type = TOKEN_PIPE};
  static t_token_content token3 = {.value = "grep",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token4 = {.value = ".c", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list4 = {.content = (void *)&token4, .next = NULL};
  static t_list token_list3 = {.content = (void *)&token3,
                               .next = &token_list4};
  static t_list token_list2 = {.content = (void *)&token2,
                               .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1,
                               .next = &token_list2};

  // AST
  static char *argv1[] = {"ls", NULL};
  static char *argv2[] = {"grep", ".c", NULL};
  static t_command cmd2 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv2, .argc = 2}};
  static t_list command_list2 = {.content = (void *)&cmd2, .next = NULL};
  static t_command cmd1 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,
      .u.simple = {.token_list = NULL, .argv = argv1, .argc = 1}};
  static t_list command_list1 = {.content = (void *)&cmd1,
                                 .next = &command_list2};
  static t_pipeline pipeline = {
      .command_list = &command_list1,
  };
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "ls | grep .c",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata cat_makefile_pipe_wc_l(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "cat", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "Makefile",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token3 = {.value = "|", .type = TOKEN_PIPE};
  static t_token_content token4 = {.value = "wc", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = "-l", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list5 = {.content = (void *)&token5, .next = NULL};
  static t_list token_list4 = {.content = (void *)&token4,
                               .next = &token_list5};
  static t_list token_list3 = {.content = (void *)&token3,
                               .next = &token_list4};
  static t_list token_list2 = {.content = (void *)&token2,
                               .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1,
                               .next = &token_list2};

  // AST
  static char *argv1[] = {"cat", "Makefile", NULL};
  static char *argv2[] = {"wc", "-l", NULL};
  static t_command cmd2 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv2, .argc = 2}};
  static t_list command_list2 = {.content = (void *)&cmd2, .next = NULL};
  static t_command cmd1 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv1, .argc = 2}};
  static t_list command_list1 = {.content = (void *)&cmd1,
                                 .next = &command_list2};
  static t_pipeline pipeline = {
      .command_list = &command_list1,
  };
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "cat Makefile | wc -l",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata ls_pipe_grep_pipe_wc(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "ls", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "|", .type = TOKEN_PIPE};
  static t_token_content token3 = {.value = "grep",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token4 = {.value = ".h", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = "|", .type = TOKEN_PIPE};
  static t_token_content token6 = {.value = "wc", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token7 = {.value = "-l", .type = TOKEN_UNQUOTED_WORD};
  static t_list token_list7 = {.content = (void *)&token7, .next = NULL};
  static t_list token_list6 = {.content = (void *)&token6,
                               .next = &token_list7};
  static t_list token_list5 = {.content = (void *)&token5,
                               .next = &token_list6};
  static t_list token_list4 = {.content = (void *)&token4,
                               .next = &token_list5};
  static t_list token_list3 = {.content = (void *)&token3,
                               .next = &token_list4};
  static t_list token_list2 = {.content = (void *)&token2,
                               .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1,
                               .next = &token_list2};

  // AST
  static char *argv1[] = {"ls", NULL};
  static char *argv2[] = {"grep", ".h", NULL};
  static char *argv3[] = {"wc", "-l", NULL};
  static t_command cmd3 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv3, .argc = 1}};

  static t_list command_list3 = {.content = (void *)&cmd3, .next = NULL};
  static t_command cmd2 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv2, .argc = 2}};

  static t_list command_list2 = {.content = (void *)&cmd2,
                                 .next = &command_list3};
  static t_command cmd1 = {
      .type = CMD_SIMPLE,
      .redir_list = NULL,

      .u.simple = {.token_list = NULL, .argv = argv1, .argc = 2}};

  static t_list command_list1 = {.content = (void *)&cmd1,
                                 .next = &command_list2};
  static t_pipeline pipeline = {
      .command_list = &command_list1,
  };
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "ls | grep .h | wc -l",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = NULL};
}
