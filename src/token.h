#ifndef TOKEN_H
#define TOKEN_H

// クォート内の文字は特殊文字として扱われないため("<"の場合リダイレクトしない）、一つの列挙型で管理したほうが好ましいらしい。念の為"TOKEN_"とつけたが、なしでも良いと思う。
typedef enum {
  TOKEN_UNQUOTED_WORD,
  TOKEN_SINGLE_QUOTED_WORD,
  TOKEN_DOUBLE_QUOTED_WORD,
  TOKEN_PIPE,
  TOKEN_REDIR_INPUT,    /* "<"   */
  TOKEN_REDIR_OUTPUT,   /* ">"   */
  TOKEN_REDIR_HERE_DOC, /* "<<"  */
  TOKEN_REDIR_APPEND,   /* ">>" */
  TOKEN_EOF
} e_token_type;

typedef struct s_token_content {
  char *value;
  e_token_type type;
} t_token_content;

#endif // !TOKEN_H
