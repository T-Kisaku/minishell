#include "testdata.h"
#include "ast.h"

t_testdata ls(){
  char *argv[] = {"ls", NULL};
  t_testdata d_ls = {
      .input      = "ls",
      .token_list = NULL,
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = 1,
            .commands = &(t_command){
              .type = CMD_SIMPLE,
              .redirs = NULL,
              .redir_count = 0,
              .u.simple = {
                .argc = 1,
                .argv = argv,
                .token_list = NULL
              }
            }
          }
        },
        .next = NULL
      }
  };
  return d_ls;
}


t_testdata echo_fire(){
  char *argv[] = {"echo", "fire",NULL};
  t_testdata d_echo_fire = {
      .input      = "echo fire",
      .token_list = NULL,
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = 1,
            .commands = &(t_command){
              .type = CMD_SIMPLE,
              .redirs = NULL,
              .redir_count = 0,
              .u.simple = {
                .argc = 1,
                .argv = argv,
                .token_list = NULL
              }
            }
          }
        },
        .next = NULL
      }
  };
  return d_echo_fire;
}
