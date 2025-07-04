/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_quote_removal_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/04 10:50:21 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "expander.h"

t_error	*redir_quote_removal_handler(t_redir *target, t_minishell_state *shell)
{
	(void)shell;
	if (target->type == REDIR_HERE_DOC)
		return (NULL);
	if (target->redirect_source.filename_token->type == TOKEN_UNQUOTED_WORD)
		return (quote_remove_core(target->redirect_source.filename_token));
	return (NULL);
}
