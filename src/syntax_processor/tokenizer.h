/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:55 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 11:15:27 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "error.h"
# include "token.h"
# include <stdbool.h> //for bool,
# include <stddef.h>  //for NULL,
# include <unistd.h>  //for write

typedef struct s_token_context
{
	t_list	**head;
	char	*start_str;
	char	*cur_str;
}			t_token_context;

t_error		*extract_and_add_token(t_token_context *ctx, t_token_type type);

t_error		*tokenize_loop(t_token_context *ctx);

t_error		*process_special_char(t_token_context *lc);
bool		is_special_char(char c);
bool		is_quote_char(char c);

#endif
