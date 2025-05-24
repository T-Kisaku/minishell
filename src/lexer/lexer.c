/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:57:41 by saueda            #+#    #+#             */
/*   Updated: 2025/05/24 19:08:52 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char	**lexser(char *string);

char	**lexser(char *string)
{
	t_token	*head;
	char	**ary;

	// head = malloc(sizeof(t_token));
	// if (!head)
	// {
	// 	write_error("malloc error \"head\"");
	// 	return (NULL);
	// }
	// head->segments = NULL;
	// head->next = NULL;
	head = NULL;
	ary = NULL;
	if (string == NULL)
		return (NULL);
	if (tokenize(&head, string) != 0)
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


