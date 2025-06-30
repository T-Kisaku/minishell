#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "syntax_processor.h"
#include "testdata.h"

static void basic_test(void);
static void redirect_test(void);
static void pipe_test(void);
static void run_test(t_testdata d);
static void print_title(const char *title);

int main(void) {
  basic_test();
  redirect_test();
  pipe_test();
  return EXIT_SUCCESS;
}

static void basic_test(void) {
  print_title("BASIC");
  run_test(ls());
  run_test(echo_simple_string());
}



static void redirect_test(void) {
  print_title("REDIRECT");
  run_test(redir_output());
  run_test(redir_append());
  run_test(redir_input());
  run_test(redir_mix());
}

static void pipe_test(void) {
  print_title("PIPE");
  run_test(ls_pipe_grep());
  run_test(cat_makefile_pipe_wc_l());
  run_test(ls_pipe_grep_h_pipe_wc_l());
}

static void run_test(t_testdata d) {
  printf("== COMMAND =====================\n%s\n", d.input);
  t_ast *ast;
  token_to_ast(d.token_list, &ast);
  expand_ast(ast);
  puts("== TEST DATA ==");
  print_ast(d.ast, 0);
  puts("== ACTUAL DATA ==");
  print_ast(ast, 0);
  assert_ast_equal(d.ast, ast);
  lstclear_and_or
(&ast);
  free_testdata(&d);
  printf("\n");
}

static void print_title(const char *title) {
  puts("===================================================================");
  puts(title);
  puts("===================================================================\n");
}
