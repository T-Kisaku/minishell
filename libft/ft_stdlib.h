/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:31:34 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:31:35 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H
# include <stddef.h>

int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);

void	*ft_realloc(void *ptr, size_t new_size);

#endif // !FT_STDLIB_H
