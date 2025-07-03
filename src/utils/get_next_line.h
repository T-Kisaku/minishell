/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:41:52 by tkisaku           #+#    #+#             */
/*   Updated: 2025/07/03 14:14:24 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef EOF
#  define EOF -1
# endif
# define READ_FAILED -1
# define SUCCEED 0
# define FAILED -10
# define INFINITY_LOOP 1

typedef struct s_string
{
	char	*string;
	size_t	length;
	size_t	capacity;
}			t_string;

// get_next_line.c
char		*get_next_line(int fd);
char		ft_getchar(int fd);
int			ft_putchar(t_string *str, char c);

// get_next_line_utils.c
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_bzero(void *s, size_t n);
void		reset_t_string(t_string *str);

#endif
