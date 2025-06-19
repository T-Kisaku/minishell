#ifndef CHECK_SYNTAX_H
# define CHECK_SYNTAX_H

# include "utils/utils.h"

typedef enum
{
	TOKEN_GROUP_WORD,
	TOKEN_GROUP_REDIR,
	TOKEN_GROUP_CONTROL_OP
}					e_token_group;

int					check_syntax(t_list *list);

#endif