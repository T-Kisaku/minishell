/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_quote_removal_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:59 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "expander.h"

t_error *redir_quote_removal_handler(t_redir *target, t_minishell_state *shell) {
	  (void)shell; // shell is not used in this function
  if (target->type == REDIR_HERE_DOC) // ヒアドクはなにもしない。
    return NULL;
  if (target->redirect_source.filename_token->type == TOKEN_SINGLE_QUOTED_WORD)
    return (NULL); // 外側がシングルクオートの場合もなにもしない
  return quote_remove_core(target->redirect_source.filename_token);
}
