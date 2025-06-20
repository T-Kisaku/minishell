
#include <stddef.h>
#include "libft.h"
#include "token.h"

t_token *copy_token(t_token token) {
  return new_token(token.value, token.type);
}

t_list *lstcopy_token(t_token token) {
  return lstnew_token(token.value, token.type);
}

t_list *lstcopy_back_token(t_list **token_list_ptr, t_token token) {
  return lstadd_back_token(token_list_ptr, token.value, token.type);
}
