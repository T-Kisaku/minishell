#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>  //for NULL,
#include <stdbool.h> //for bool,
#include <stdlib.h> //for malloc, free
#include <unistd.h> //for write
#include "libft.h"
#include "token.h"
#include "utils/utils.h"

// 構造体リストを作成するために関数内で使用する構造体
typedef struct s_token_context {
  t_list **head;
  t_list *cur_token;
  char *start_str;
  char *cur_str;
} t_token_context;

// tokenizer.c
t_list *tokenizer(char *string);
// processes.c
int create_token(t_token_context *ctx);
int set_token(t_token_context *ctx, e_token_type type);
void process_space(t_token_context *ctx);
int process_quoted_word(t_token_context *ctx);
int process_unquoted_word(t_token_context *ctx);
// process_special_char.c
int process_special_char(t_token_context *lc);
// utils.c
int write_error(char *msg);

//for test
int main();
#endif
