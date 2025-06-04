#ifndef TESTDATA_H
#define TESTDATA_H

#include "ast.h"

typedef struct s_testdata {
  char *input;
  t_token_list token_list;
  t_ast ast;
} t_testdata;


// basic
t_testdata ls(void);
t_testdata echo_hello(void);

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

#endif // !TESTDATA_H
