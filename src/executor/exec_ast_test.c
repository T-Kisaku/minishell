#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "testdata.h"

static void test(t_testdata d) {
  printf("== COMMAND =====================\n");
  printf("%s\n", d.input);
  printf("== OUTPUT ======================\n");

  exec_ast(&d.ast);
  printf("\n\n");
}

int main() {
  puts("===================================================================");
  puts(" Basic");
  puts("===================================================================\n");
  test(ls());
  test(echo_hello());

  puts("===================================================================");
  puts(" Redirect");
  puts("===================================================================\n");
  test(redir_output());
  test(redir_append());
  test(redir_input());
  test(redir_mix());
  test(pipe_to_redir());

  puts("===================================================================");
  puts("Pipe");
  puts("===================================================================\n");
  test(ls_pipe_grep());
  test(cat_makefile_pipe_wc_l());
  return (EXIT_SUCCESS);
}
