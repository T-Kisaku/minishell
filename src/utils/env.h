/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
#define ENV_H
#include "libft.h"
#include "error.h"

typedef struct s_env {
  char *key;
  char *value;
} t_env;

typedef struct s_env_state {
  t_list *list;
  char **array;
  bool dirty;
} t_env_state;

t_env *new_env(char *key, char *value);
t_env *str_to_new_env(char *env_str);
t_list *lstnew_env(char *env_str);
t_error *envp_to_env_list(char **envp, t_list **env_list_ptr);
t_error *env_list_to_envp(t_list *env_list, char ***envp_ptr);

t_env *lstget_env(t_list *node);
bool cmp_env_key(void *target, void *content);
t_error *ms_getenv( char *search_key, char **value_ptr, t_list *env_list);

void del_env(void *content);
void lstclear_env(t_list **head);

#endif // !ENV_H
