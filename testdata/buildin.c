#include "testdata.h"

// Builtin command edge cases

t_testdata cd_noarg(void) {
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
      .input = "cd", .token_list = {0}, .ast = ast, .output_file = NULL};
}

t_testdata cd_non_existing_dir(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata export_two_vars(void) {
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
                      .token_list = {0},
                      .ast = ast,
                      .output_file = NULL};
}

t_testdata unset_then_echo(void) {
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
                      .token_list = {0},
                      .ast = list1,
                      .output_file = NULL};
}

t_testdata exit_status_42(void) {
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
      .input = "exit 42", .token_list = {0}, .ast = ast, .output_file = NULL};
}
