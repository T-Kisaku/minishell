#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ast.h"
#include "error.h"
#include "minishell.h"
#include "exit_status.h"
#include "utils/env.h"

static void easy_test();
static void builtin_test();
static void redirect_test();
static void pipe_test();
static void test(char *input_str, int expected_status, char *output_file);
static void print_title(char *title);
static void print_file_content(char filename[]);
static char **copy_env(char **envp);
static void free_env(char **env);
t_list *g_env_list = NULL;

int main(int _, char **__, char **envp) {
  t_error *err = envp_to_env_list(envp, &g_env_list);
  if (err)
    del_error(err);
  /* easy_test(); */
  builtin_test();
  /* redirect_test(); */
  /* pipe_test(); */

  lstclear_env(&g_env_list);
  return (EXIT_SUCCESS);
}

static void easy_test() {
  print_title("EXTERNAL");
  test("ls", EXIT_OK, NULL);
  test("cat /etc/os-release", EXIT_OK, NULL);
}

static void export_unset_test();
static void exit_test();
static void echo_test();
static void builtin_test() {
  print_title("BUILTIN");
  // pwd
  /* test("pwd", EXIT_OK, NULL); */
  /* test("pwd wow", EXIT_USER_ERR, NULL); */
  // env
  /* test("env", EXIT_OK, NULL); */
  /* test("env wow", EXIT_USER_ERR, NULL); */
  // export
  export_unset_test();
  // cd
  /* exit_test(); */
  /* echo_test(); */
}

static void export_unset_test() {

  test("export", EXIT_OK, NULL);
  test("export FIRE=FIRE | env | grep FIRE", EXIT_OK,
       NULL); // use and in the feature
  test("export FIRE=WATER | env | grep FIRE", EXIT_OK,
       NULL); // use and in the feature
  test("unset FIRE | env | grep FIRE", 1,
       NULL); // use and in the feature
}
static void exit_test() {
  test("minishell -c 'exit'", EXIT_OK, NULL);
  test("minishell -c 'exit 42'", 42, NULL);
  test("minishell -c 'exit +123'", 123, NULL);
  test("minishell -c 'exit -456'", 56, NULL);
  test("minishell -c 'exit 0'", 0, NULL);
  test("minishell -c 'exit 0 123 456'", EXIT_USER_ERR, NULL);
  test("minishell -c 'exit abc'", EXIT_USER_ERR, NULL);
  test("minishell -c 'exit +abc'", EXIT_USER_ERR, NULL);
  test("minishell -c 'exit -abc'", EXIT_USER_ERR, NULL);
  test("minishell -c 'exit 255'", 255, NULL);
  test("minishell -c 'exit +999'", 231, NULL);
}
static void echo_test() {

  test("echo", EXIT_OK, NULL);
  test("echo hello", EXIT_OK, NULL);
  test("echo -n wow", EXIT_OK, NULL);
  test("echo -n wow wow nice to meet you", EXIT_OK, NULL);
}

static void redirect_test() {
  print_title("REDIRECT");
  test("echo hello >out.txt", EXIT_OK, "out.txt");
  test("echo bye >>out.txt", EXIT_OK, "out.txt");
  test("cat <out.txt", EXIT_OK, NULL);
  test("cat < out.txt > new.txt", EXIT_OK, "new.txt");
}

static void pipe_test() {
  print_title("PIPE");
  test("ls | grep .c", EXIT_OK, NULL);
  test("cat Makefile | wc -l", EXIT_OK, NULL);
  test("ls | grep .h | wc -l", EXIT_OK, "out.txt");
}

static void test(char *input_str, int expected_status, char *output_file) {
  t_ast *ast;
  t_error *err = str_to_ast(input_str, &ast);
  err = expand_ast(ast);
  printf("== COMMAND =====================\n");
  printf("%s\n", input_str);
  printf("== STDOUT ======================\n");
  int result_status = exec_ast(ast, &g_env_list);
  if (output_file) {
    printf("== %s ======================\n", output_file);
    print_file_content(output_file);
  }
  printf("== SIGNAL ======================\n");
  printf("Expected: %d\n", expected_status);
  printf("Result  : %d\n", result_status);
  assert(expected_status == result_status);
  printf("\n");
  lstclear_and_or
(&ast);
  del_error(err);
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
