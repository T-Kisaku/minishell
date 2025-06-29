/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:15:50 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 13:22:47 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_SYNTAX_H
# define CHECK_SYNTAX_H

# include "error.h"
# include "ft_list.h"
# include "minishell.h"

t_error	*check_body(t_list **cur, t_list **prev);
t_error	*check_tail(t_list **list, t_minishell_state *shell);

#endif // !CHECK_SYNTAX_H
