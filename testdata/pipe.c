#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"

t_testdata ls_pipe_grep(void) {
  t_ast *ast_ptr = NULL;
  t_and_or *last_andor = NULL;
  t_command *last_cmd = NULL;

  last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("ls", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "ls");
  last_andor = get_last_and_or(&ast_ptr);
  last_cmd = lstget_command(
      lstadd_back_command(&last_andor->pipeline->command_list, CMD_SIMPLE));
  last_cmd->u.simple.argv = gen_argv("grep", ".c", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list =
      gen_token_list(2, TOKEN_UNQUOTED_WORD, "grep", TOKEN_UNQUOTED_WORD, ".c");
  return ((t_testdata){
      .input = "ls | grep .c",
      .token_list = gen_token_list(4, TOKEN_UNQUOTED_WORD, "ls", TOKEN_PIPE,
                                   "|", TOKEN_UNQUOTED_WORD, "grep",
                                   TOKEN_UNQUOTED_WORD, ".c"),
      .ast = ast_ptr,
      .output_file = NULL,
  });
}
t_testdata cat_makefile_pipe_wc_l(void) {
  t_ast *ast_ptr = NULL;
  t_and_or *last_andor = NULL;
  t_command *last_cmd = NULL;

  last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("cat", "Makefile", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(
      2, TOKEN_UNQUOTED_WORD, "cat", TOKEN_UNQUOTED_WORD, "Makefile");

  last_andor = get_last_and_or(&ast_ptr);
  last_cmd = lstget_command(
      lstadd_back_command(&last_andor->pipeline->command_list, CMD_SIMPLE));
  last_cmd->u.simple.argv = gen_argv("wc", "-l", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list =
      gen_token_list(2, TOKEN_UNQUOTED_WORD, "wc", TOKEN_UNQUOTED_WORD, "-l");

  return (t_testdata){
      .input = "cat Makefile | wc -l",
      .token_list =
          gen_token_list(5, TOKEN_UNQUOTED_WORD, "cat", TOKEN_UNQUOTED_WORD,
                         "Makefile", TOKEN_PIPE, "|", TOKEN_UNQUOTED_WORD, "wc",
                         TOKEN_UNQUOTED_WORD, "-l"),
      .ast = ast_ptr,
      .output_file = NULL,
  };
}

t_testdata ls_pipe_grep_h_pipe_wc_l(void) {
  t_ast *ast_ptr = NULL;
  t_and_or *last_andor = NULL;
  t_command *last_cmd = NULL;

  last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("ls", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "ls");

  last_andor = get_last_and_or(&ast_ptr);
  last_cmd = lstget_command(
      lstadd_back_command(&last_andor->pipeline->command_list, CMD_SIMPLE));
  last_cmd->u.simple.argv = gen_argv("grep.h", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list =
      gen_token_list(1, TOKEN_UNQUOTED_WORD, "grep.h");

  last_andor = get_last_and_or(&ast_ptr);
  last_cmd = lstget_command(
      lstadd_back_command(&last_andor->pipeline->command_list, CMD_SIMPLE));
  last_cmd->u.simple.argv = gen_argv("wc", "-l", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list =
      gen_token_list(2, TOKEN_UNQUOTED_WORD, "wc", TOKEN_UNQUOTED_WORD, "-l");

  return (t_testdata){
      .input = "ls | grep.h | wc -l",
      .token_list =
          gen_token_list(6, TOKEN_UNQUOTED_WORD, "ls", TOKEN_PIPE, "|",
                         TOKEN_UNQUOTED_WORD, "grep.h", TOKEN_PIPE, "|",
                         TOKEN_UNQUOTED_WORD, "wc", TOKEN_UNQUOTED_WORD, "-l"),
      .ast = ast_ptr,
      .output_file = NULL,
  };
}
