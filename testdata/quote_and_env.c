#include "testdata.h"

// Quote and environment variable handling

t_testdata echo_env_home(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata echo_no_expand_home(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata echo_concat_user(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata export_and_echo(void) {
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
      .input = "export VAR=test ; echo $VAR", .token_list = {0}, .ast = list1};
}

t_testdata echo_status(void) {
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
      .input = "echo $?", .token_list = {0}, .ast = ast, .output_file = NULL};
}
