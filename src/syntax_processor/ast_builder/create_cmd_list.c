#include "ast.h"
#include <stdlib.h>

int create_command_list(t_list **cmd_list);
static t_command *create_command(void);
static void set_simple(u_command *u);

int create_command_list(t_list **cmd_list) {
  t_list *new;

  new = malloc(sizeof(t_list));
  if (!new)
    return (1);
  new->next = NULL;
  new->content = create_command();
  if (new->content == NULL) {
    free(new);
    return (1);
  }
  ft_lstadd_back(cmd_list, new);
  return (0);
}

static t_command *create_command(void) {
  t_command *cmd;

  cmd = malloc(sizeof(t_command));
  if (!cmd)
    return (NULL);
  cmd->type = CMD_SIMPLE;
  cmd->redir_list = NULL;
  if (cmd->type == CMD_SIMPLE)
    set_simple(&cmd->u);
  return (cmd);
}

static void set_simple(u_command *u) {
  u->simple.token_list = NULL;
  u->simple.argv = NULL;
  u->simple.argc = 0;
}
