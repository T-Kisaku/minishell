#ifndef TESTDATA_H
#define TESTDATA_H

#include "ast.h"

typedef struct s_testdata {
  char *input;
  t_list token_list;
  t_ast ast;
  char *output_file;
} t_testdata;

// basic
t_testdata ls(void);
t_testdata echo_hello(void);
t_testdata cat_nofile(void);

// builtin
t_testdata pwd(void);
// builtin edge cases
t_testdata cd_noarg(void);
t_testdata cd_non_existing_dir(void);
t_testdata export_two_vars(void);
t_testdata unset_then_echo(void);
t_testdata exit_status_42(void);

// pipe
t_testdata ls_pipe_grep(void);
t_testdata cat_makefile_pipe_wc_l(void);
t_testdata ls_pipe_grep_pipe_wc(void);

// quote and env
t_testdata echo_env_home(void);
t_testdata echo_no_expand_home(void);
t_testdata echo_concat_user(void);
t_testdata export_and_echo(void);
t_testdata echo_status(void);

// redirect
t_testdata redir_output(void);
t_testdata redir_input(void);
t_testdata redir_append(void);
t_testdata redir_mix(void);
t_testdata pipe_to_redir(void);

// syntax error
t_testdata err_unclosed_quote(void);
t_testdata err_bad_redir(void);
t_testdata err_pipe_position(void);
t_testdata err_single_redirect(void);

// print functions
void print_token_list(t_list *token_list);

void print_ast(t_ast *ast, int indent);
void print_and_or(t_and_or *and_or, int indent);
void print_pipeline(t_pipeline *pipeline, int indent);
void print_command(t_command *cmd, int indent);
void print_redirection(t_list *redir_list, int indent);

// assert functions
void assert_token_list(t_list *expected, t_list *actual);
#endif // !TESTDATA_H
