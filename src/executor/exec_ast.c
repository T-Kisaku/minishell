#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "ast.h"
#include "minishell.h"
#include "executor.h"

// TODO: have satatus at the top levele and return it;
int exec_ast(t_ast *ast) {
  t_list *list = ast;
  while (list) {
    t_and_or *andor = list->first_and_or;
    int status = 0;
    int exec_next = 1;
    while (andor) {
      if (exec_next)
        status = run_pipeline(&andor->pipeline);
      if (andor->op_next == OP_AND)
        exec_next = (status == 0);
      else if (andor->op_next == OP_OR)
        exec_next = (status != 0);
      else
        exec_next = 1;
      andor = andor->next;
    }
    list = list->next;
  }
  return 0;
}
