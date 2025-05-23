/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:28:31 by saueda            #+#    #+#             */
/*   Updated: 2025/05/22 17:28:04 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
//for NULL,
# include <stddef.h>

typedef enum
{
	UNQUOTED_WORD,
	SINGLE_QUOTED_WORD,
	DOUBLE_QUOTED_WORD
}						e_segment_type;

typedef struct s_segment
{
	char				*value;
	e_segment_type		type;
	struct s_segment	*next;
}						t_segment;

typedef struct s_token
{
	t_segment			*segments;
	struct s_token		*next;
}						t_token;

typedef struct s_lexer_context
{
	t_token				*cur_token;
	t_token				*prev_token;
	t_segment			*cur_seg;
	t_segment			*prev_seg;
	char				*start_str;
	char				*cur_str;
}						t_lexer_context;

char	**lexser(char *string);
int	set_tokens(t_token *head, char *string);
int	process_unquoted(t_lexer_context *lc);
int	process_quoted(t_lexer_context *lc, e_segment_type seg_type);
static int	ft_isspace(int c);
int	write_error_return_error(char *msg);
void	clean_tokens(t_token **head);


//for test
void print_tokens(const t_token *head);
int main(void);
#endif