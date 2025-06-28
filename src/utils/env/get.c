#include <stdlib.h>
#include "libft.h"
#include "ft_list.h"
#include "utils/env.h"
#include "ft_string.h"

t_env *lstget_env(t_list *node) {
  if (!node || !node->content)
    return (NULL);
  return ((t_env *)node->content);
}

#include <stdio.h>
bool cmp_env_key(void *target, void *content) {
  t_env *casted_target;
  t_env *casted_content;
  casted_target = NULL;
  casted_content = NULL;
  if (target == NULL || content == NULL)
    return false;
  casted_target = (t_env *)target;
  casted_content = (t_env *)content;
  return ft_strcmp(casted_target->key, casted_content->key) == 0;
}

char *ms_getenv(t_list *env_list, char *search_key) {
  t_env *search_env;
  t_env *found;
  search_env = new_env(search_key, "dummy");
  found = ft_lstfind(env_list, search_env, cmp_env_key);
  del_env(search_env);
  if (!found || !found->value)
    return NULL;
  return ft_strdup(found->value);
}
