#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include "ast.h"
#include "error.h"
#include "minishell.h"
#include "executor.h"

// same meaning as exec_and_or
t_error *exec_ast(t_ast *ast) {
  t_list *andor_list;
  t_and_or *andor;
  t_error *error;
  bool exec_next;
  andor_list = ast;
  error = NULL;
  exec_next = true;
  while (andor_list) {
    andor = lstget_and_or(ast);
    if (exec_next) {
      del_error(error);
      error = exec_pipeline(andor->pipeline);
    }
    if (andor->op_next == OP_AND)
      exec_next = !is_error(error);
    else if (andor->op_next == OP_OR)
      exec_next = true;
    else
      break;
    andor_list = andor_list->next;
  }
  return error;
}
