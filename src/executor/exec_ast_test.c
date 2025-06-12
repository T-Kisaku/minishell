#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "minishell.h"
#include "testdata.h"

static void basic_test();
static void redirect_test();
static void pipe_test();
static void test(t_testdata d, int expected_status);

int main() {
  basic_test();
  redirect_test();
  pipe_test();
  return (EXIT_SUCCESS);
}

static void basic_test() {

  puts("===================================================================");
  puts(" Basic");
  puts("===================================================================\n");
  test(ls(), EXIT_SUCCESS);
  test(echo_hello(), EXIT_SUCCESS);
  test(cat_nofile(), EXIT_FAILURE);
}

static void redirect_test() {

  puts("===================================================================");
  puts(" Redirect");
  puts("===================================================================\n");
  test(redir_output(), EXIT_SUCCESS);
  test(redir_append(), EXIT_SUCCESS);
  test(redir_input(), EXIT_SUCCESS);
  test(redir_mix(), EXIT_SUCCESS);
  test(pipe_to_redir(), EXIT_SUCCESS);
}

static void pipe_test() {

  puts("===================================================================");
  puts("Pipe");
  puts("===================================================================\n");
  test(ls_pipe_grep(), EXIT_SUCCESS);
  test(cat_makefile_pipe_wc_l(), EXIT_SUCCESS);
  test(ls_pipe_grep_pipe_wc(), EXIT_SUCCESS);
}

static void test(t_testdata d, int expected_status) {
  printf("== COMMAND =====================\n");
  printf("%s\n", d.input);
  /* printf("== AST     =====================\n"); */
  /* print_ast(&d.ast, 0); */
  printf("== STDOUT ======================\n");
  int result_status = exec_ast(&d.ast);
  printf("== SIGNAL ======================\n");
  printf("Expected: %d\n", expected_status);
  printf("Result  : %d\n", result_status);
  assert(expected_status == result_status);
  printf("\n");
}
