/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 11:17:06 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_QUOTE_H
# define CHECK_QUOTE_H

# include "error.h"
# include "minishell.h"

t_error	*check_quote(char **input, t_minishell_state *shell);

#endif