/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:12 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/18 13:42:55 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SUCCESS 1
#define FAILED 0

static int	count_words(char *str, char sep)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str && *str != sep)
		{
			count++;
			while (*str && *str != sep)
				str++;
		}
	}
	return (count);
}

static char	*word_dup(char *start_p, char *end_p)
{
	char	*word;
	char	*ptr;

	word = malloc((end_p - start_p + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ptr = word;
	while (start_p < end_p)
		*ptr++ = *start_p++;
	*ptr = '\0';
	return (word);
}

static int	free_str_arr(char **str_arr, int str_arr_size)
{
	int	splited_i;

	splited_i = 0;
	while (splited_i < str_arr_size)
	{
		free(str_arr[splited_i]);
		splited_i++;
	}
	free(str_arr);
	return (FAILED);
}

static int	split_str_arr(char const *s, char c, char **splited,
		int splited_size)
{
	char	*word;
	int		word_i;
	char	*start_p;

	word_i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			start_p = (char *)s;
			while (*s && *s != c)
				s++;
			word = word_dup(start_p, (char *)s);
			if (!word)
				return (free_str_arr(splited, splited_size));
			splited[word_i] = word;
			word_i++;
		}
	}
	splited[word_i] = NULL;
	return (SUCCESS);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		splited_size;

	splited_size = (count_words((char *)s, c) + 1);
	splited = ft_calloc(splited_size, sizeof(char *));
	if (!splited)
		return (NULL);
	if (split_str_arr(s, c, splited, splited_size) == FAILED)
		return (NULL);
	return (splited);
}
