#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "minishell.h"
#include "testdata.h"
#include "exit_status.h"

static void easy_test();
static void builtin_test();
static void redirect_test();
static void pipe_test();
static void test(t_testdata d, int expected_status);
static void print_title(char *title);
static void print_file_content(char filename[]);
static char **copy_env(char **envp);
static void free_env(char **env);
char **g_envp;

int main(int _, char **__, char **envp) {
  g_envp = copy_env(envp);
  easy_test();
  builtin_test();
  redirect_test();
  pipe_test();

  free_env(g_envp);
  return (EXIT_SUCCESS);
}

static void easy_test() {
  print_title("EASY");
  test(ls(), EXIT_SUCCESS);
  test(echo_simple_string(), EXIT_SUCCESS);
  /* test(cat_nofile(), EXIT_FAILURE); */
}

static void builtin_test() {
  print_title("BUILTIN");
  test(pwd(), EXIT_SUCCESS);
  test(pwd_with_arg(), EXIT_USER_ERR);
  test(env(), EXIT_SUCCESS);
  test(env_with_arg(), EXIT_USER_ERR);
  test(echo_no_args(), EXIT_SUCCESS);
  test(echo_simple_string(), EXIT_SUCCESS);
  test(echo_with_n_option(), EXIT_SUCCESS);
  test(echo_with_n_option_multiple_words(), EXIT_SUCCESS);
}

static void redirect_test() {
  print_title("REDIRECT");
  test(redir_output(), EXIT_SUCCESS);
  test(redir_append(), EXIT_SUCCESS);
  test(redir_input(), EXIT_SUCCESS);
  test(redir_mix(), EXIT_SUCCESS);
}

static void pipe_test() {
  print_title("PIPE");
  test(ls_pipe_grep(), EXIT_SUCCESS);
  test(cat_makefile_pipe_wc_l(), EXIT_SUCCESS);
}

static void test(t_testdata d, int expected_status) {
  printf("== COMMAND =====================\n");
  printf("%s\n", d.input);
  /* printf("== AST     =====================\n"); */
  /* print_ast(d.ast, 0); */
  printf("== STDOUT ======================\n");
  int result_status = exec_ast(d.ast, g_envp);
  if (d.output_file) {
    printf("== %s ======================\n", d.output_file);
    print_file_content(d.output_file);
  }
  printf("== SIGNAL ======================\n");
  printf("Expected: %d\n", expected_status);
  printf("Result  : %d\n", result_status);
  assert(expected_status == result_status);
  printf("\n");
  free_testdata(&d);
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

static char **copy_env(char **envp) {
  int i = 0;
  while (envp[i])
    i++;

  char **copy = malloc(sizeof(char *) * (i + 1));
  for (int j = 0; j < i; j++)
    copy[j] = strdup(envp[j]);
  copy[i] = NULL;
  return copy;
}

static void free_env(char **env) {
  if (!env)
    return;
  for (int i = 0; env[i]; i++)
    free(env[i]); // 各文字列を解放
  free(env);      // 配列本体を解放
}
