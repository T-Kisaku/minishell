/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreduce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:30:25 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 12:30:26 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_strreduce(char const *s, void *init, void *(*f)(unsigned int, char,
			void *))
{
	void			*accumulated;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	accumulated = init;
	i = 0;
	while (s[i])
	{
		accumulated = f(i, s[i], accumulated);
		i++;
	}
	return (accumulated);
}
