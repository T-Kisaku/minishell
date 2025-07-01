/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/01 13:33:01 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ft_string.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = -1;
	redir->to_be_redirected.is_direct_to_fd = false;
	redir->to_be_redirected.fd = -1;
	redir->to_be_redirected.filename = NULL;
	redir->to_be_redirected.filename_token = NULL;
	redir->redirect_source.is_direct_to_fd = false;
	redir->redirect_source.fd = -1;
	redir->redirect_source.filename = NULL;
	redir->redirect_source.filename_token = NULL;
	return (redir);
}

static int	init_filename_token(t_redir *new, t_token *filename_token)
{
	new->redirect_source.filename_token = malloc(sizeof(t_token));
	if (!new->redirect_source.filename_token)
		return (EXIT_FAILURE);
	new->redirect_source.filename_token->value
		= ft_strdup(filename_token->value);
	if (!new->redirect_source.filename_token->value)
	{
		free(new->redirect_source.filename_token);
		return (EXIT_FAILURE);
	}
	new->redirect_source.filename_token->type = filename_token->type;
	return (EXIT_SUCCESS);
}

static int	set_redirect_fd(t_redir *new, t_redir_type redir_type)
{
	new->to_be_redirected.is_direct_to_fd = true;
	if (redir_type == REDIR_INPUT || redir_type == REDIR_HERE_DOC)
		new->to_be_redirected.fd = STDIN_FILENO;
	else if (redir_type == REDIR_OUTPUT || redir_type == REDIR_APPEND)
		new->to_be_redirected.fd = STDOUT_FILENO;
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_list	*lstnew_redir(t_redir_type redir_type, t_token *filename_token)
{
	t_redir	*new;
	t_list	*new_list;

	new = new_redir();
	if (!new)
		return (NULL);
	new->type = redir_type;
	if (init_filename_token(new, filename_token) != EXIT_SUCCESS)
	{
		del_redir(new);
		return (NULL);
	}
	if (set_redirect_fd(new, redir_type) != EXIT_SUCCESS)
	{
		del_redir(new);
		return (NULL);
	}
	new_list = ft_lstnew((void *)new);
	if (!new_list)
	{
		del_redir(new);
		return (NULL);
	}
	return (new_list);
}

t_list	*lstadd_back_redir(t_list **redir_list_ptr, t_redir_type redir_type,
		t_token *filename_token)
{
	t_list	*new_list;

	new_list = lstnew_redir(redir_type, filename_token);
	ft_lstadd_back(redir_list_ptr, new_list);
	return (new_list);
}
