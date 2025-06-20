#include <stddef.h>
#include "libft.h"
#include "token.h"

void del_token(void *content) {
  t_token *token;

  if (!content)
    return;
  token = (t_token *)content;
  free(token->value);
  free(token);
}

void lstclear_token(t_list **head) {
  if (!head || !*head)
    return;
  ft_lstclear(head, del_token);
}
