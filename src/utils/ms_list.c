#include "libft.h"
#include "utils/ms_list.h"
void *lstfind(t_list *lst, void *search_content, bool (*cmp)(void *, void *)) {
  while (lst) {
    if (cmp(search_content, lst->content)) {
      return lst->content;
    }
    lst = lst->next;
  }
  return NULL;
}

void lstunset(t_list **lst, void *search_content, bool (*cmp)(void *, void *),
              void (*del)(void *)) {
  t_list *curr = *lst;
  t_list *prev = NULL;

  while (curr) {
    if (cmp(search_content, curr->content)) {
      if (prev)
        prev->next = curr->next;
      else
        *lst = curr->next;
      ft_lstdelone(curr, del);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}
