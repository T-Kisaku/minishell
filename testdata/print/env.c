#include <stdio.h>
#include "utils/env.h"

void print_env(void *content) {
  if (content == NULL)
    printf("NULL\n");
  else
    printf("%s: %s\n", ((t_env *)content)->key, ((t_env *)content)->value);
}

void print_env_list(t_list *env_list) { ft_lstiter(env_list, print_env); }
