#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "minishell.h"
#include "executor.h"

// same meaning as exec_and_or
int exec_ast(t_ast *ast) {
  t_list *andor_list;
  t_and_or *andor;
  int status;
  bool exec_next;
  andor_list = ast;
  status = EXIT_SUCCESS;
  exec_next = true;
  while (andor_list) {
    andor = lstget_and_or(ast);
    if (exec_next)
      status = exec_pipeline(andor->pipeline);
    if (andor->op_next == OP_AND)
      exec_next = (status == EXIT_SUCCESS);
    else if (andor->op_next == OP_OR)
      exec_next = EXIT_SUCCESS;
    else
      break;
    andor_list = andor_list->next;
  }
  return status;
}
