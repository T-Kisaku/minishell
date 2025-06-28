#ifndef CHECK_SYNTAX_H
#define CHECK_SYNTAX_H

#include "error.h"
#include "ft_list.h"
#include "minishell.h"

typedef enum {
  TOKEN_GROUP_WORD,
  TOKEN_GROUP_REDIR,
  TOKEN_GROUP_CONTROL_OP
} e_token_group;

t_error *check_syntax(t_list **list, t_minishell_state *shell);

#endif
