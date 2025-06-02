#include "testdata.h"
#include "ast.h"

t_testdata ls(){
  char *argv[] = {"ls", NULL};
  t_testdata testdata_ls = {
      .input      = "ls",
      .token_list = (t_token_list){
        .token = &(t_token){
          .token = "ls",
          .flags = 0
        },
        .next=NULL
      },
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = 1,
            .commands = &(t_command){
              .type = CMD_SIMPLE,
              .redirs = NULL,
              .redir_count = 0,
              .u.simple = {.argc = 1, .argv = argv}
            }
          }
        },
        .next = NULL
      }
  };
  return testdata_ls;
}


t_testdata echo(){
  char *argv[] = {"echo", "hello",NULL};
  /* t_token_list token_list = { */
  /*   .token = &(t_token){.token = "echo", .flags = 0}, */
  /*   .next = &(t_token_list){ */
  /*     .token = &(t_token){ */
  /*       .token = "hello", */
  /*       .flags = 0 */
  /*     }, */
  /*     .next = NULL */
  /*   } */
  /* }; */
  t_testdata testdata_echo = {
      .input      = "echo hello",
      .token_list = NULL,
      .ast        = {
        .first_and_or = &(t_and_or){
          .pipeline = {
            .cmd_count = 1,
            .commands = &(t_command){
              .type = CMD_SIMPLE,
              .redirs = NULL,
              .redir_count = 0,
              .u.simple = {.argc = 1, .argv = argv}
            }
          }
        },
        .next = NULL
      }
  };
  return testdata_echo;
}
