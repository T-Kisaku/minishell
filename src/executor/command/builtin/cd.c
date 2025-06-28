/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "executor/command/builtin.h"
#include "exit_status.h"
#include "libft.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "utils/env.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "utils/path.h"

void set_env(void *content, void *ideal) {
  t_env *casted_content;
  t_env *casted_ideal;
  casted_content = (t_env *)content;
  casted_ideal = (t_env *)ideal;
  free(casted_content->key);
  free(casted_content->value);
  casted_content->key = ft_strdup(casted_ideal->key);
  casted_content->value = ft_strdup(casted_ideal->value);
}

void *lstinsert(t_list **lst_ptr, void *ideal_content,
                bool (*cmp)(void *, void *), void (*set)(void *, void *)) {

  void *found;
  found = ft_lstfind(*lst_ptr, ideal_content, cmp);
  if (!found) {
    ft_lstadd_back(lst_ptr, ft_lstnew(ideal_content));
    return ft_lstlast(*lst_ptr);
  }
  set(found, ideal_content);
  return found;
}

int exec_cd(t_command *cmd, t_list **env_list_ptr) {
  char *pwd;
  char *oldpwd;
  t_env *ideal;
  t_error *error;
error = NULL;
  if (cmd->type != CMD_SIMPLE) {
    ft_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }
  if (cmd->u.simple.argc > 2) {
    ft_fputs("cd: too many arguments", STDERR_FILENO);
    return EXIT_USER_ERR;
  }
  if (cmd->u.simple.argc == 1)
    error = ms_getenv("HOME", &pwd, *env_list_ptr);
  else
    pwd = ft_strdup(cmd->u.simple.argv[1]);
if(is_error(error)) {
	ft_fputs(error->msg, STDERR_FILENO);
	del_error(error);
	return error->exit_code;
  }
  if (!pwd)
    return (EXIT_OK);
  if (!is_cd_target_valid(pwd)) {
    free(pwd);
    return (EXIT_USER_ERR);
  }
  if (chdir(pwd) != 0) {
    printf("cd: %s: %s\n", pwd, strerror(errno));
    free(pwd);
    return EXIT_USER_ERR;
  }
  ideal = new_env("PWD", pwd);
  free(pwd);
  lstinsert(env_list_ptr, ideal, cmp_env_key, set_env);
  del_env(ideal);
  oldpwd = getcwd(NULL, 0);
  ideal = new_env("OLDPWD", oldpwd);
  free(oldpwd);
  lstinsert(env_list_ptr, ideal, cmp_env_key, set_env);
  del_env(ideal);
  return (EXIT_OK);
}
