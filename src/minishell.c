#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "error.h"
#include "utils/ms_string.h"
#include "ast.h"
#include "exit_status.h"
#include "minishell.h"

static int run_cmd(char *argv);
static bool process_option_c(int argc, char **argv);
static bool prompt(void);

int main(int argc, char **argv) {
  if (process_option_c(argc, argv))
    return (EXIT_SUCCESS);
  if (argc > 1) {
    user_error("minishell except only -c flags\n");
    return (EXIT_USER_ERR);
  }

  while (1)
    if (prompt())
      break;

  return (EXIT_SUCCESS);
}

static int run_cmd(char *input) {
  t_ast *ast;
  int status;
  ast = NULL;
  status = EXIT_OK;
  if (!input) {
    printf("\n");
    return status;
  }
  status = str_to_ast(input, &ast);
  if (status != EXIT_OK) {
    return status;
  }

  status = process_expansion(ast);
  if (status != EXIT_OK) {
    free_ast(&ast);
    return status;
  }
  status = exec_ast(ast);
  free_ast(&ast);
  return status;
}

static bool process_option_c(int argc, char **argv) {
  if (!(argc == 3 && ms_strcmp(argv[1], "-c") == 0))
    return false;
  run_cmd(argv[2]);
  return true;
}

// Return whether it should exit
static bool prompt(void) {
  /* int status; */
  char *input_str;
  input_str = readline("minishell$");
  if (!input_str) {
    printf("exit\n");
    return true;
  }
  if (*input_str)
    add_history(input_str);
  /* status = run_cmd(input_str); */
  run_cmd(input_str);
  // TODO: make sure free input even if exit is called in run_cmd!!
  free(input_str);
  return false;
}
