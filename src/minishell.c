#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "ms_string.h"

static void run_cmd(char *argv);
static bool process_option_c(int argc, char **argv);
static bool prompt(void);

int main(int argc, char **argv) {
  if (process_option_c(argc, argv))
    return (EXIT_SUCCESS);
  if (argc > 1) {
    // TODO: replace correct error handling
    printf("OPTION ERROR\n");
    return (EXIT_FAILURE);
  }

  while (1)
    if (prompt())
      break;

  return (EXIT_SUCCESS);
}

static void run_cmd(char *input) {
  printf("PROMPTED: %s\n", input);
  /* t_ast ast = parse(argv); */
  /* execute_ast(ast); */
  /* free_ast(ast); */
}
static bool process_option_c(int argc, char **argv) {
  if (!(argc == 3 && ms_strcmp(argv[1], "-c") == 0))
    return false;
  run_cmd(argv[2]);
  return true;
}

// Return whether it should exit
static bool prompt(void) {
  /* t_data data; */
  /* data.lexered = NULL; */
  /* data.parsered = NULL; */
  /* data.lexered = lexer(argv); */
  /* data.parsered = (data.lexered); */
  /* executor(data.parsered); */
  /* cleanup(data); */

  char *input;
  input = readline("minishell$");
  if (!input) {
    printf("exit\n");
    return true;
  }
  if (*input)
    add_history(input);
  run_cmd(input);
  // TODO: make sure free input even if exit is called in run_cmd!!
  free(input);
  return false;
}
