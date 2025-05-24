/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:28:31 by saueda            #+#    #+#             */
/*   Updated: 2025/05/24 19:40:15 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
//for NULL,
# include <stddef.h>
//for bool,
# include <stdbool.h>

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
	t_token				**head;
	t_token				*cur_token;
	t_token				*prev_token;
	t_segment			*cur_seg;
	t_segment			*prev_seg;
	char				*start_str;
	char				*cur_str;
	bool				need_new_token;
	
}						t_lexer_context;

//lexer.c
char	**lexser(char *string);
//tokenize.c
int			tokenize(t_token**head, char *string);
//ensure_token_segment.c
int ensure_token_and_segment(t_lexer_context *lc);
//process_special_char.c
int	process_special_char(t_lexer_context *lc);
//process_others.c
void	process_space(t_lexer_context *lc);
int		process_quoted(t_lexer_context *lc, e_segment_type seg_type);
int		process_unquoted(t_lexer_context *lc);
int	set_segment_value(t_lexer_context *lc, e_segment_type type);
//utils.c
int	write_error(char *msg);
int syntax_error(const char *token, size_t len);
void	clean_tokens(t_token **head);
int	ft_isspace(int c);

//for test
void print_tokens(const t_token *head);
int main(void);
#endif