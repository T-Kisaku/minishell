#include "ast.h"
#include "testdata.h"
#include "token.h"
#include <unistd.h>

// Redirection examples

t_testdata redir_output(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "hello",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token3 = {.value = ">", .type = TOKEN_REDIR_OUTPUT};
  static t_token_content token4 = {.value = "out.txt",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = "", .type = TOKEN_EOF};
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
  static char *argv[] = {"echo", "hello", NULL};
  static t_redir redir = {.type = REDIR_OUTPUT,
                          .from =
                              {
                                  .is_direct_to_fd = true,
                                  .fd = STDOUT_FILENO,
                                  .filename = NULL,
                                  .filename_token = NULL,
                              },
                          .to = {
                              .is_direct_to_fd = false,
                              .fd = -1,
                              .filename = "out.txt",
                              .filename_token = NULL,
                          }};
  static t_list redir_list = {.content = (void *)&redir, .next = NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = &redir_list,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo hello > out.txt",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = "out.txt"};
}

t_testdata redir_input(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "cat", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "<", .type = TOKEN_REDIR_INPUT};
  static t_token_content token3 = {.value = "out.txt",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token4 = {.value = "", .type = TOKEN_EOF};
  static t_list token_list4 = {.content = (void *)&token4, .next = NULL};
  static t_list token_list3 = {.content = (void *)&token3,
                               .next = &token_list4};
  static t_list token_list2 = {.content = (void *)&token2,
                               .next = &token_list3};
  static t_list token_list1 = {.content = (void *)&token1,
                               .next = &token_list2};

  // AST
  static char *argv[] = {"cat", NULL};
  static t_redir redir = {.type = REDIR_INPUT,
                          .from =
                              {
                                  .is_direct_to_fd = true,
                                  .fd = STDIN_FILENO,
                                  .filename = NULL,
                                  .filename_token = NULL,
                              },
                          .to = {
                              .is_direct_to_fd = false,
                              .fd = -1,
                              .filename = "out.txt",
                              .filename_token = NULL,
                          }};
  static t_list redir_list = {.content = (void *)&redir, .next = NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = &redir_list,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 1}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){
      .input = "cat < out.txt", .token_list = token_list1, .ast = ast};
}

t_testdata redir_append(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "bye", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token3 = {.value = ">>", .type = TOKEN_REDIR_APPEND};
  static t_token_content token4 = {.value = "out.txt",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = "", .type = TOKEN_EOF};
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
  static char *argv[] = {"echo", "bye", NULL};
  static t_redir redir = {.type = REDIR_APPEND,
                          .from =
                              {
                                  .is_direct_to_fd = true,
                                  .fd = STDOUT_FILENO,
                                  .filename = NULL,
                                  .filename_token = NULL,
                              },
                          .to = {
                              .is_direct_to_fd = false,
                              .fd = -1,
                              .filename = "out.txt",
                              .filename_token = NULL,
                          }};
  static t_list redir_list = {.content = (void *)&redir, .next = NULL};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = &redir_list,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 2}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo bye >> out.txt",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = "out.txt"};
}

t_testdata redir_mix(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "cat", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "<", .type = TOKEN_REDIR_INPUT};
  static t_token_content token3 = {.value = "out.txt",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token4 = {.value = ">", .type = TOKEN_REDIR_OUTPUT};
  static t_token_content token5 = {.value = "new.txt",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token6 = {.value = "", .type = TOKEN_EOF};
  static t_list token_list6 = {.content = (void *)&token6, .next = NULL};
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
  static char *argv[] = {"cat", NULL};
  static t_redir redir1 = {.type = REDIR_INPUT,
                           .from =
                               {
                                   .is_direct_to_fd = true,
                                   .fd = STDIN_FILENO,
                                   .filename = NULL,
                                   .filename_token = NULL,
                               },
                           .to = {
                               .is_direct_to_fd = false,
                               .fd = -1,
                               .filename = "out.txt",
                               .filename_token = NULL,
                           }};
  static t_redir redir2 = {.type = REDIR_OUTPUT,
                           .from =
                               {
                                   .is_direct_to_fd = true,
                                   .fd = STDOUT_FILENO,
                                   .filename = NULL,
                                   .filename_token = NULL,
                               },
                           .to = {
                               .is_direct_to_fd = false,
                               .fd = -1,
                               .filename = "new.txt",
                               .filename_token = NULL,
                           }};
  static t_list redir_list2 = {.content = (void *)&redir2, .next = NULL};
  static t_list redir_list1 = {.content = (void *)&redir1,
                               .next = &redir_list2};
  static t_command cmd = {
      .type = CMD_SIMPLE,
      .redir_list = &redir_list1,
      .u.simple = {.token_list = NULL, .argv = argv, .argc = 1}};
  static t_list cmd_list = {.content = (void *)&cmd, .next = NULL};
  static t_pipeline pipeline = {.command_list = &cmd_list};
  static t_and_or and_or = {
      .pipeline = &pipeline,
      .op_next = OP_NONE,
  };
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "cat < out.txt > new.txt",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = "new.txt"};
}

t_testdata pipe_to_redir(void) {
  // TOKEN LIST
  static t_token_content token1 = {.value = "echo",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token2 = {.value = "test",
                                   .type = TOKEN_SINGLE_QUOTED_WORD};
  static t_token_content token3 = {.value = "|", .type = TOKEN_PIPE};
  static t_token_content token4 = {.value = "cat", .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token5 = {.value = ">", .type = TOKEN_REDIR_OUTPUT};
  static t_token_content token6 = {.value = "result.txt",
                                   .type = TOKEN_UNQUOTED_WORD};
  static t_token_content token7 = {.value = "", .type = TOKEN_EOF};
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
  static char *argv1[] = {"echo", "test", NULL};
  static char *argv2[] = {"cat", NULL};
  static t_redir redir2 = {.type = REDIR_OUTPUT,
                           .from =
                               {
                                   .is_direct_to_fd = true,
                                   .fd = STDOUT_FILENO,
                                   .filename = NULL,
                                   .filename_token = NULL,
                               },
                           .to = {
                               .is_direct_to_fd = false,
                               .fd = -1,
                               .filename = "result.txt",
                               .filename_token = NULL,
                           }};
  static t_list redir_list2 = {.content = (void *)&redir2, .next = NULL};
  static t_command cmd1 = {
      .type = CMD_SIMPLE,
      .u.simple = {.token_list = NULL, .argv = argv1, .argc = 2}};

  static t_command cmd2 = {
      .type = CMD_SIMPLE,
      .redir_list = &redir_list2,
      .u.simple = {.token_list = NULL, .argv = argv2, .argc = 1}};
  static t_list cmd_list2 = {.content = (void *)&cmd2, .next = NULL};
  static t_list cmd_list1 = {.content = (void *)&cmd1, .next = &cmd_list2};
  static t_pipeline pipeline = {.command_list = &cmd_list1};
  static t_and_or and_or = {.pipeline = &pipeline, .op_next = OP_NONE};
  static t_ast ast = {.content = (void *)&and_or, .next = NULL};
  return (t_testdata){.input = "echo 'test' | cat > result.txt",
                      .token_list = token_list1,
                      .ast = ast,
                      .output_file = "result.txt"};
}
