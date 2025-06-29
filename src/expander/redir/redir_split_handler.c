/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_split_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:59 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 09:32:40 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "ft_string.h"
#include "minishell.h"
#include "token.h"
#include <stdbool.h>

static bool	check_could_not_split(char *value);

t_error	*redir_split_handler(t_redir *redir, t_minishell_state *shell)
{
	(void)shell;
	if (redir->type == REDIR_HERE_DOC)
		return (NULL);
	if (redir->redirect_source.filename_token->type == TOKEN_UNQUOTED_WORD)
	{
		if (check_could_not_split(redir->redirect_source.filename_token->value)
			!= 0)
			return (new_error(EXIT_INTERNAL_ERR, "could't splited!!"));
	}
	return (NULL);
}

static bool	check_could_not_split(char *value)
{
	while (*value)
	{
		if (ft_isspace(*value))
			return (true);
	}
	return (false);
}
