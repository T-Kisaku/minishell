/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:03:50 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 11:21:02 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "utils/env.h"
#include <stdlib.h>

void del_shell_state(t_minishell_state *shell)
{
  lstclear_env(&shell->env_list);
  lstclear_and_or(&shell->ast);
  free(shell->pids);
}

