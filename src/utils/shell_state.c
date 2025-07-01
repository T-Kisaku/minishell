/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:03:50 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 13:10:20 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "utils/env.h"
#include <stdlib.h>

void	del_shell_state(t_minishell_state *shell)
{
	lstclear_env(&shell->env_list);
	lstclear_and_or(&shell->ast);
	free(shell->pids);
}
