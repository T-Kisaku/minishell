#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>  //for NULL,
#include <stdbool.h> //for bool,
#include "token.h"

// 構造体リストを作成するために関数内で使用する構造体
typedef struct s_token_context {
  t_token_list **head;
  t_token_list *cur_token;
  char *start_str;
  char *cur_str;
} t_token_context;

// tokenizer.c
t_token_list *tokenizer(char *string);
// processes.c
int create_token(t_token_context *tc);
int set_token(t_token_context *tc, e_token_type type);
void process_space(t_token_context *tc);
int process_quoted_word(t_token_context *tc);
int process_unquoted_word(t_token_context *tc);
// process_special_char.c
int process_special_char(t_token_context *lc);
// utils.c
int write_error(char *msg);
void clean_tokens(t_token_list **head);
int ft_isspace(int c);

#endif
