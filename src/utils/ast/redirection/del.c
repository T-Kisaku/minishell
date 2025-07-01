/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:45:38 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
#include <stddef.h>

void	del_redir(void *ptr)
{
	t_redir	*redir;

	redir = (t_redir *)ptr;
	if (!redir)
		return ;
	free(redir->redirect_source.filename);
	del_token(redir->redirect_source.filename_token);
	free(redir->to_be_redirected.filename);
	del_token(redir->to_be_redirected.filename_token);
	free(redir);
}
// TODO: free filename_token here

void	clear_redir_list(t_list **head)
{
	if (!head || !*head)
		return ;
	ft_lstclear(head, del_redir);
}
