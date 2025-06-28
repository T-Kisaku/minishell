#ifndef MS_LIST
#define MS_LIST

#include <stdbool.h>
#include "libft.h"

void *lstfind(t_list *lst, void *search, bool (*cmp)(void *, void *));
void lstunset(t_list **lst, void *search_content, bool (*cmp)(void *, void *),
              void (*del)(void *));
#endif // !MS_LIST
