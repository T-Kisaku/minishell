#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "utils/env.h"
#include "exit_status.h"

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

t_error *ms_getenv( char *search_key, char **value_ptr, t_list *env_list) {
  t_env *search_env;
  t_env *found;
  char *target;
  search_env = new_env(search_key, "dummy");
  found = ft_lstfind(env_list, search_env, cmp_env_key);
  if(found == NULL)
	target="";
 else
	target =found->value;
  *value_ptr = ft_strdup(target);
  del_env(search_env);
  if(!(*value_ptr)) {
	return new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR");
  }
  return NULL;
}

// t_error *ms_getenv(char *search_key, char **value_ptr, t_list *env_list) {
//     t_env search_env;
//     t_env *found;

//     // 比較用の一時オブジェクトをスタック領域で作る（malloc/free不要）
//     search_env.key = search_key;
//     search_env.value = NULL; // valueは比較に不要ならNULLでOK

//     found = lstfind(env_list, &search_env, cmp_env_key);
//     if(found == NULL) {
//         return new_error(EXIT_USER_ERR, "ENVIRONMENT VARIABLE NOT FOUND");
//     }
//     *value_ptr = ft_strdup(found->value);
//     if(!(*value_ptr)) {
//         return new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR");
//     }
//     return NULL;
// }


