#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include "libft.h"

// クォート内の文字は特殊文字として扱われないため("<"の場合リダイレクトしない）、一つの列挙型で管理したほうが好ましいらしい。念の為"TOKEN_"とつけたが、なしでも良いと思う。
typedef enum e_token_type {
  TOKEN_UNQUOTED_WORD,
  TOKEN_SINGLE_QUOTED_WORD, // '
  TOKEN_DOUBLE_QUOTED_WORD, // "
  TOKEN_PIPE,               // |
  TOKEN_AND_IF,             // &&
  TOKEN_OR_IF,              // ||
  TOKEN_REDIR_INPUT,        // <
  TOKEN_REDIR_OUTPUT,       // >
  TOKEN_REDIR_HERE_DOC,     // <<
  TOKEN_REDIR_HERE_STRINGS, // <<<
  TOKEN_REDIR_APPEND,       // >>
} t_token_type;

typedef struct t_token {
  char *value;
  t_token_type type;
} t_token;

void del_token(void *content);
void lstclear_token(t_list **head);
t_token *lstget_token(t_list *node);
t_token *new_token(char *value, t_token_type type);
t_list *lstnew_token(char *value, t_token_type type);
t_list *lstadd_back_token(t_list **token_list_ptr, char *value,
                          t_token_type type);

t_token *copy_token(t_token token);
t_list *lstcopy_token(t_token token);
t_list *lstcopy_back_token(t_list **token_list_ptr, t_token token);
bool is_word_token(t_token_type type);
bool is_redir_token(t_token_type type);
bool is_control_op_token(t_token_type type);

#endif // !TOKEN_H
