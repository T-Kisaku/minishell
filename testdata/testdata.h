#ifndef TESTDATA_H
#define TESTDATA_H

#include "ast.h"
#include "error.h"

typedef struct s_testdata {
  char *input;
  t_list *token_list;
  t_ast *ast;
  char *output_file;
} t_testdata;

// ls
t_testdata ls(void);
t_testdata ls_with_args(void);

// pwd
t_testdata pwd(void);
t_testdata pwd_with_arg(void);
// env
t_testdata env(void);
t_testdata env_with_arg(void);
// exit
t_testdata exit_no_args(void);
t_testdata exit_with_number(void);
t_testdata exit_with_plus_prefix(void);
t_testdata exit_with_minus_prefix(void);
t_testdata exit_with_zero(void);
t_testdata exit_with_multiple_args(void);
t_testdata exit_with_invalid_arg(void);
t_testdata exit_with_plus_invalid(void);
t_testdata exit_with_minus_invalid(void);
t_testdata exit_with_large_number(void);
t_testdata exit_with_plus_large_number(void);
// echo
t_testdata echo_no_args(void);
t_testdata echo_simple_string(void);
t_testdata echo_with_n_option(void);
t_testdata echo_with_n_option_multiple_words(void);

// builtin edge cases
t_testdata cd_noarg(void);
t_testdata cd_non_existing_dir(void);
t_testdata export_two_vars(void);
t_testdata unset_then_echo(void);
t_testdata exit_status_42(void);

// pipe
t_testdata ls_pipe_grep(void);
t_testdata cat_makefile_pipe_wc_l(void);
t_testdata ls_pipe_grep_h_pipe_wc_l(void);

// redirect
t_testdata redir_output(void);
t_testdata redir_output_nospace(void);
t_testdata redir_input(void);
t_testdata redir_append(void);
t_testdata redir_mix(void);

// syntax error
t_testdata err_unclosed_quote(void);
t_testdata err_bad_redir(void);
t_testdata err_pipe_position(void);
t_testdata err_single_redirect(void);

// print functions
void print_token_list(t_list *token_list);
void print_env_list(t_list *env_list);

void print_ast(t_ast *ast, int indent);
void print_and_or(t_and_or *and_or, int indent);
void print_pipeline(t_pipeline *pipeline, int indent);
void print_command(t_command *cmd, int indent);
void print_redirection(t_list *redir_list, int indent);

// assert functions
void assert_token_list_equal(t_list *exp, t_list *act, const char *path);
void assert_ast_equal(t_ast *expected, t_ast *actual);

// generate functions
t_list *gen_token_list(int count, ...);
char **gen_argv(char *first, ...);
int gen_argc(char **argv);

void free_testdata(t_testdata *d);

void check_error(t_error *error);
#endif // !TESTDATA_H
