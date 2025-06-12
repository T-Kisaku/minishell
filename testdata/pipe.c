#include "testdata.h"

// Pipe related commands

t_testdata ls_pipe_grep(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata cat_makefile_pipe_wc_l(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata ls_pipe_grep_pipe_wc(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}
