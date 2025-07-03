/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:03:50 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:27:23 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "utils/env.h"
#include <stdlib.h>
#include <unistd.h>

void	init_shell_state(t_minishell_state *shell)
{
	shell->ast = NULL;
	shell->env_list = NULL;
	shell->pids = NULL;
	shell->env_list = NULL;
	shell->prev_exit_code = 0;
	shell->is_interactive = false;
}

void	del_shell_state(t_minishell_state *shell)
{
	lstclear_env(&shell->env_list);
	lstclear_and_or(&shell->ast);
	free(shell->pids);
}
