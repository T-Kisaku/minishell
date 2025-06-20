#include "ast.h"
void del_pipeline(t_pipeline *pipe) {
  if (!pipe)
    return;
  lstclear_cmd(&pipe->command_list);
  free(pipe);
}
