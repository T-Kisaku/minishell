/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "minishell.h"

t_error *generate_filename_handler(t_redir *target, t_minishell_state *shell) {
	(void)shell;
  if (target->type == REDIR_HERE_DOC)
    return (NULL);
  if (target->redirect_source.is_direct_to_fd)
    return (NULL);
  target->redirect_source.filename =
      ft_strdup(target->redirect_source.filename_token->value);
  if (!target->redirect_source.filename)
    return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
  return (NULL);
}
