#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "minishell.h"
#include "testdata.h"

static void basic_test();
static void builtin_test();
static void redirect_test();
static void pipe_test();
static void test(t_testdata d, int expected_status);
static void print_title(char *title);
static void print_file_content(char filename[]);

int main() {
  /* basic_test(); */
  builtin_test();
  /* redirect_test(); */
  /* pipe_test(); */
  return (EXIT_SUCCESS);
}

static void basic_test() {
  print_title("BASIC");
  test(ls(), EXIT_SUCCESS);
  test(echo_hello(), EXIT_SUCCESS);
  test(cat_nofile(), EXIT_FAILURE);
}

static void builtin_test() {
  print_title("BUILTIN");
  test(pwd(), EXIT_SUCCESS);
}

static void redirect_test() {
  print_title("REDIRECT");
  test(redir_output(), EXIT_SUCCESS);
  test(redir_append(), EXIT_SUCCESS);
  test(redir_input(), EXIT_SUCCESS);
  test(redir_mix(), EXIT_SUCCESS);
  test(pipe_to_redir(), EXIT_SUCCESS);
}

static void pipe_test() {
  print_title("PIPE");
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
  if (d.output_file) {
    printf("== %s ======================\n", d.output_file);
    print_file_content(d.output_file);
  }
  printf("== SIGNAL ======================\n");
  printf("Expected: %d\n", expected_status);
  printf("Result  : %d\n", result_status);
  assert(expected_status == result_status);
  printf("\n");
}

static void print_title(char *title) {
  puts("===================================================================");
  puts(title);
  puts("===================================================================\n");
}

static void print_file_content(char filename[]) {
  FILE *file;
  int ch;
  file = fopen(filename, "r"); // Open for reading
  if (file == NULL) {
    perror("Error opening file");
  }
  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
  fclose(file);
}
