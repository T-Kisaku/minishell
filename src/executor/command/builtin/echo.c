/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:57 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "ast.h"
#include "exit_status.h"
#include "ft_stdio.h"
#include "ft_string.h"

// TODO: fix echo > test.txt
// Redirect is broken
// space exits at the last when echo is executed
int exec_echo(t_command *cmd, t_list *env_list) {
  int i;
  bool is_new_line;
  (void)env_list;
  if (cmd->type != CMD_SIMPLE) {
    ft_fputs("cmd->type should be CMD_SIMPLE bro", STDERR_FILENO);
    return EXIT_INTERNAL_ERR;
  }
  i = 1;
  is_new_line = true;

  while (i < cmd->u.simple.argc && cmd->u.simple.argv[i] != NULL) {
    if (i == 1 && ft_strcmp(cmd->u.simple.argv[i], "-n") == 0) {
      is_new_line = false;
      i++;
      continue;
    }
    if (i + 1 == cmd->u.simple.argc)
      printf("%s", cmd->u.simple.argv[i]);
    else
      printf("%s ", cmd->u.simple.argv[i]);
    i++;
  }
  if (is_new_line)
    printf("\n");
  return (EXIT_OK);
}
