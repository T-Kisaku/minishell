#include "testdata.h"
#include "ast.h"

t_testdata ls_pipe_grep(){
  char *ls_argv[] = {"ls", NULL};
  int ls_argc = 1;
  char *grep_argv[] = {"grep", ".c", NULL};
  int grep_argc = 2;
  t_command cmds[] = {
    {
      .type = CMD_SIMPLE,
      .redirs = NULL,
      .redir_count = 0,
      .u.simple = {.argc = ls_argc, .argv = ls_argv}
    },
    {
      .type = CMD_SIMPLE,
      .redirs = NULL,
      .redir_count = 0,
      .u.simple = {.argc = grep_argc, .argv = grep_argv}
    },
    NULL
  };
  int cmd_count = 2;
  t_testdata d_ls_pipe_grep = {
      .input      = "ls | grep .c",
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


t_testdata ls_pipe_grep_pipe_wc(){

  char *ls_argv[] = {"ls", NULL};
  int ls_argc = 1;
  char *grep_argv[] = {"grep", ".h", NULL};
  int grep_argc = 2;
  char *wl_argv[] = {"wl", "-l", NULL};
  int wl_argc = 2;
  t_command cmds[] = {
    {
      .type = CMD_SIMPLE,
      .redirs = NULL,
      .redir_count = 0,
      .u.simple = {.argc = ls_argc, .argv = ls_argv}
    },
    {
      .type = CMD_SIMPLE,
      .redirs = NULL,
      .redir_count = 0,
      .u.simple = {.argc = grep_argc, .argv = grep_argv}
    },
    {
      .type = CMD_SIMPLE,
      .redirs = NULL,
      .redir_count = 0,
      .u.simple = {.argc = wl_argc, .argv = wl_argv}
    },
    NULL
  };
  int cmd_count = 3;
  t_testdata d_ls_pipe_grep_pipe_wc = {
      .input      = "ls | grep .h | wc -l",
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
  return d_ls_pipe_grep_pipe_wc;
}


