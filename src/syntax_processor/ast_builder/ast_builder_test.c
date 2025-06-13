#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "syntax_processor.h"
#include "testdata.h"
#include "utils/utils.h"

static void basic_test(void);
static void builtin_test(void);
static void redirect_test(void);
static void pipe_test(void);
static void run_test(t_testdata d);
static void print_title(const char *title);

int main(void) {
  basic_test();
  builtin_test();
  redirect_test();
  pipe_test();
  return EXIT_SUCCESS;
}

static void basic_test(void) {
  print_title("BASIC");
  run_test(ls());
  run_test(echo_hello());
  run_test(cat_nofile());
}

static void builtin_test(void) {
  print_title("BUILTIN");
  run_test(pwd());
}

static void redirect_test(void) {
  print_title("REDIRECT");
  run_test(redir_output());
  run_test(redir_append());
  run_test(redir_input());
  run_test(redir_mix());
  run_test(pipe_to_redir());
}

static void pipe_test(void) {
  print_title("PIPE");
  run_test(ls_pipe_grep());
  run_test(cat_makefile_pipe_wc_l());
  run_test(ls_pipe_grep_pipe_wc());
}

static void run_test(t_testdata d) {
  printf("== COMMAND =====================\n%s\n", d.input);
  t_ast *ast = ast_builder(&d.token_list);
  assert_ast_equal(&d.ast, ast);
  free_ast(&ast);
  printf("\n");
}

static void print_title(const char *title) {
  puts("===================================================================");
  puts(title);
  puts("===================================================================\n");
}
