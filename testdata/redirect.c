#include "testdata.h"
#include "ast.h"

t_testdata redir_output (){
  char *echo_hello_argv[] = {"echo", "hello",NULL};
  int echo_hello_argc = 2;
  t_redir redirs[] = {{.type = REDIR_OUTPUT, .target = "out.txt"},NULL};
  t_command cmds[] = {
    {
      .type = CMD_SIMPLE,
      .redirs = redirs,
      .redir_count = 1,
      .u.simple = {.argc = echo_hello_argc, .argv = echo_hello_argv}
    },
    NULL
  };
  int cmd_count = 1;
  t_testdata d_ls_pipe_grep = {
      .input      = "echo hello > out.txt",
      .token_list = NULL,
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = cmd_count,
            .commands = cmds
          }
        },
        .next = NULL
      }
  };
  return d_ls_pipe_grep;
}


t_testdata redir_input (){
  char *cat_argv[] = {"cat",NULL};
  int cat_argc = 1;
  t_redir redirs[] = {{.type = REDIR_INPUT, .target = "out.txt"},NULL};
  t_command cmds[] = {
    {
      .type = CMD_SIMPLE,
      .redirs = redirs,
      .redir_count = 1,
      .u.simple = {.argc = cat_argc, .argv = cat_argv}
    },
    NULL
  };
  int cmd_count = 1;
  t_testdata d_ls_pipe_grep = {
      .input      = "cat < out.txt",
      .token_list = NULL,
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = cmd_count,
            .commands = cmds
          }
        },
        .next = NULL
      }
  };
  return d_ls_pipe_grep;
}

t_testdata redir_append (){
  char *cat_argv[] = {"cat",NULL};
  int cat_argc = 1;
  t_redir redirs[] = {{.type = REDIR_INPUT, .target = "out.txt"},NULL};
  t_command cmds[] = {
    {
      .type = CMD_SIMPLE,
      .redirs = redirs,
      .redir_count = 1,
      .u.simple = {.argc = cat_argc, .argv = cat_argv}
    },
    NULL
  };
  int cmd_count = 1;
  t_testdata d_ls_pipe_grep = {
      .input      = "cat < out.txt",
      .token_list = NULL,
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = cmd_count,
            .commands = cmds
          }
        },
        .next = NULL
      }
  };
  return d_ls_pipe_grep;
}
