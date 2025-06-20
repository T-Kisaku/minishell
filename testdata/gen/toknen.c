#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "token.h"

t_list *gen_token_list(int count, ...) {
  va_list args;
  t_list *head = NULL;
  t_list *last = NULL;

  va_start(args, count);

  for (int i = 0; i < count; ++i) {
    t_token_type type = va_arg(args, t_token_type);
    char *value = va_arg(args, char *);

    t_list *new_node = lstnew_token(value, type);
    if (!new_node) {
      // エラー処理：既存のリストを解放
      ft_lstclear(
          &head,
          del_token); // free_token: t_token* を解放する関数を実装しておく
      va_end(args);
      return NULL;
    }

    if (!head)
      head = new_node;
    else
      ft_lstadd_back(&last, new_node);

    last = new_node;
  }

  va_end(args);
  return head;
}
