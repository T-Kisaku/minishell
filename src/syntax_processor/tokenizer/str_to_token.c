/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_status.h"
#include "syntax_processor/tokenizer.h"

static t_error *tokenize(t_list **head, char *string);

t_error *str_to_token(char *input_str, t_list **token_list_ptr) {
  t_error *error;
  error = NULL;
  if (input_str == NULL)
    return new_error(EXIT_INTERNAL_ERR,
                     "ERROR: I don't know why input is NULL, LOL");
  error = tokenize(token_list_ptr, input_str);
  if (is_error(error)) {
    lstclear_token(token_list_ptr);
    return error;
  }
  return error;
}

static t_error *tokenize(t_list **head, char *string) {
  t_token_context ctx;

  ctx.head = head;
  ctx.start_str = string;
  ctx.cur_str = string;
  return tokenize_loop(&ctx);
}
