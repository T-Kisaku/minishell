/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:57:41 by saueda            #+#    #+#             */
/*   Updated: 2025/05/22 17:40:01 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char		**lexser(char *string);
int			set_tokens(t_token *head, char *string);
int			process_unquoted(t_lexer_context *lc);
int			process_quoted(t_lexer_context *lc, e_segment_type seg_type);
static int	ft_isspace(int c);
int			write_error_return_error(char *msg);
void		clean_tokens(t_token **head);

char	**lexser(char *string)
{
	t_token	*head;
	char	**ary;

	head = malloc(sizeof(t_token));
	if (!head)
	{
		write_error_return_error("malloc error \"head\"");
		return (NULL);
	}
	head->segments = NULL;
	head->next = NULL;
	ary = NULL;
	if (string == NULL)
	{
		clean_tokens(&head);
		return (NULL);
	}
	if (set_tokens(head, string) != 0)
	{
		clean_tokens(&head);
		return (NULL);
	}
	// if (set_char_ary(&head, &ary) != 0)
	// {
	// 	clean_tokens(&head);
	// 	return (NULL);
	// }
	clean_tokens(&head);
	return (ary);
}

int	set_tokens(t_token *head, char *string)
{
	t_lexer_context	lc;

	lc.cur_token = head;
	lc.prev_token = NULL;
	lc.cur_seg = lc.cur_token->segments;
	lc.prev_seg = NULL;
	lc.start_str = string;
	while (ft_isspace(*lc.start_str))
		lc.start_str++;
	while (*lc.start_str)
	{
		lc.cur_str = lc.start_str;
		if (*lc.cur_str == '\0')
			break ;
		else if (ft_isspace(*lc.cur_str))
		{
			lc.prev_token = lc.cur_token;
			lc.cur_token = malloc(sizeof(t_token));
			if (!lc.cur_token)
				return (write_error_return_error("malloc error \"cur_token\""));
			lc.cur_token->next = NULL;
			lc.cur_token->segments = NULL;
			if (lc.prev_token)
				lc.prev_token->next = lc.cur_token;
			lc.prev_seg = NULL;
			while (ft_isspace(*lc.cur_str))
				lc.cur_str++;
			lc.start_str = lc.cur_str;
			continue ;
		}
		if (*lc.cur_str == '\'')
		{
			if (process_quoted(&lc, SINGLE_QUOTED_WORD) != 0)
				return (1);
			continue ;
		}
		else if (*lc.cur_str == '"')
		{
			if (process_quoted(&lc, DOUBLE_QUOTED_WORD) != 0)
				return (1);
			continue ;
		}
		else
		{
			if (process_unquoted(&lc) != 0)
				return (1);
			continue ;
		}
	}
	return (0);
}

//unquoted string
int	process_unquoted(t_lexer_context *lc)
{
	lc->cur_seg = malloc(sizeof(t_segment));
	if (!lc->cur_seg)
		return (write_error_return_error("malloc error \"cur_seg\""));
	if (lc->prev_seg)
		lc->prev_seg->next = lc->cur_seg;
	else
		lc->cur_token->segments = lc->cur_seg;
	lc->cur_seg->next = NULL;
	lc->cur_seg->value = NULL;
	while (*lc->cur_str != '\0' && !ft_isspace(*lc->cur_str)
		&& *lc->cur_str != '\'' && *lc->cur_str != '"')
		lc->cur_str++;
	lc->cur_seg->value = malloc(sizeof(char) *
								(lc->cur_str - lc->start_str + 1));
	if (!lc->cur_seg->value)
		return (write_error_return_error("malloc error \"value\""));
	ft_memcpy(lc->cur_seg->value, lc->start_str, lc->cur_str - lc->start_str);
	lc->cur_seg->value[lc->cur_str - lc->start_str] = '\0';
	lc->cur_seg->type = UNQUOTED_WORD;
	lc->prev_seg = lc->cur_seg;
	lc->start_str = lc->cur_str;
	return (0);
}

//quoted string
int	process_quoted(t_lexer_context *lc, e_segment_type seg_type)
{
	char	quote;

	lc->cur_seg = malloc(sizeof(t_segment));
	if (!lc->cur_seg)
		return (write_error_return_error("malloc error \"cur_seg\""));
	if (lc->prev_seg)
		lc->prev_seg->next = lc->cur_seg;
	else
		lc->cur_token->segments = lc->cur_seg;
	lc->cur_seg->next = NULL;
	lc->cur_seg->value = NULL;
	lc->start_str++;
	lc->cur_str++;
	if (seg_type == SINGLE_QUOTED_WORD)
		quote = '\'';
	else if (seg_type == DOUBLE_QUOTED_WORD)
		quote = '"';
	else
		return (write_error_return_error("bad segment_type on process_in_quote"));
	while (*lc->cur_str != '\0' && *lc->cur_str != quote)
		lc->cur_str++;
	if (*lc->cur_str == '\0')
		return (write_error_return_error("unclosed quotes"));
	lc->cur_seg->value = malloc(sizeof(char) *
								(lc->cur_str - lc->start_str + 1));
	if (!lc->cur_seg->value)
		return (write_error_return_error("malloc error \"value\""));
	ft_memcpy(lc->cur_seg->value, lc->start_str, lc->cur_str - lc->start_str);
	lc->cur_seg->value[lc->cur_str - lc->start_str] = '\0';
	lc->cur_seg->type = seg_type;
	lc->prev_seg = lc->cur_seg;
	lc->start_str = ++lc->cur_str;
	return (0);
}

//space return 1 is true
static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}

//write error and return error
int	write_error_return_error(char *msg)
{
	char	*prefix;

	prefix = "minishell: ";
	write(2, prefix, ft_strlen(prefix));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

void	clean_tokens(t_token **head)
{
	t_token		*cur_token;
	t_token		*next_token;
	t_segment	*cur_seg;
	t_segment	*next_seg;

	cur_token = *head;
	if (*head)
	{
		while (cur_token)
		{
			cur_seg = cur_token->segments;
			while (cur_seg)
			{
				free(cur_seg->value);
				next_seg = cur_seg->next;
				free(cur_seg);
				cur_seg = next_seg;
			}
			next_token = cur_token->next;
			free(cur_token);
			cur_token = next_token;
		}
		*head = NULL;
	}
}
