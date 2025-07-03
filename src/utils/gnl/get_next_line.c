/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:33:15 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:17:17 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/get_next_line.h"

char	ft_getchar(int fd)
{
	static char		buf[BUFFER_SIZE];
	static char		*bufp;
	static ssize_t	bytes;

	if (bytes == 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == READ_FAILED)
		{
			bufp = NULL;
			bytes = 0;
			return (FAILED);
		}
		bufp = buf;
	}
	if (--bytes >= 0)
		return (*bufp++);
	else
		return (EOF);
}

// str->length + 1 + 1: Old-Allocation + New-Allocation + Null-Terminate
int	ft_putchar(t_string *str, char c)
{
	char	*new_str;

	if (c == EOF)
		return (SUCCEED);
	if (str->length + 1 + 1 > str->capacity)
	{
		str->capacity += BUFFER_SIZE + 1;
		new_str = ft_calloc(str->capacity, sizeof(char));
		if (new_str == NULL)
			return (FAILED);
		ft_strlcpy(new_str, str->string, str->length + 1);
		free(str->string);
		str->string = new_str;
	}
	str->string[str->length] = c;
	str->length++;
	return (SUCCEED);
}

int	finalize_string(t_string *str)
{
	char	*exact_str;

	if (str->string == NULL)
		return (FAILED);
	exact_str = ft_calloc(str->length + 1, sizeof(char));
	if (exact_str == NULL)
		return (FAILED);
	str->capacity = str->length + 1;
	ft_strlcpy(exact_str, str->string, str->length + 1);
	free(str->string);
	str->string = exact_str;
	return (SUCCEED);
}

/*
 * Return NULL if error occured or there is nothing else to read
 * Return \n execept if EOF
 */
char	*get_next_line(int fd)
{
	t_string	ret;
	char		c;

	if (fd < 0)
		return (NULL);
	ret.string = NULL;
	reset_t_string(&ret);
	while (INFINITY_LOOP)
	{
		c = ft_getchar(fd);
		if (c == FAILED || ft_putchar(&ret, c) == FAILED)
		{
			reset_t_string(&ret);
			break ;
		}
		if (c == '\n' || c == EOF)
			break ;
	}
	if (ret.length == 0 || finalize_string(&ret) == FAILED)
		reset_t_string(&ret);
	return (ret.string);
}
