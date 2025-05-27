/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:57:41 by saueda            #+#    #+#             */
/*   Updated: 2025/05/27 12:33:08 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

char	**lexser(char *string);

char	**lexser(char *string)
{
	t_token	*head;
	char	**ary;

	head = NULL;
	ary = NULL;
	if (string == NULL)
		return (NULL);
	if (tokenize(&head, string) != 0)	
	{
		clean_tokens(&head);
		return (NULL);
	}
	// if (expander(head) != 0)
	// {
	// 	clean_tokens(&head);
	// 	return (NULL);
	// }
	if (set_char_ary(head, &ary) != 0)
	{
		clean_tokens(&head);
		return (NULL);
	}
	clean_tokens(&head);
	return (ary);
}


