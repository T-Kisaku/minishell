/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>  //for NULL,
#include <stdbool.h> //for bool,
#include <unistd.h>  //for write
#include "error.h"
#include "libft.h"
#include "token.h"

// 構造体リストを作成するために関数内で使用する構造体
typedef struct s_token_context {
  t_list **head;
  char *start_str;
  char *cur_str;
} t_token_context;

t_error *extract_and_add_token(t_token_context *ctx, t_token_type type);

t_error *tokenize_loop(t_token_context *ctx);

t_error *process_special_char(t_token_context *lc);
bool is_special_char(char c);
#endif
