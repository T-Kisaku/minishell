#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>  //for NULL,
#include <stdbool.h> //for bool,
#include <unistd.h>  //for write
#include "libft.h"
#include "token.h"

// 構造体リストを作成するために関数内で使用する構造体
typedef struct s_token_context {
  t_list **head;
  char *start_str;
  char *cur_str;
} t_token_context;

int extract_and_add_token(t_token_context *ctx, t_token_type type);

int tokenize_loop(t_token_context *ctx);

int process_special_char(t_token_context *lc);
int is_special_char(char c);
#endif
