/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:11 by tkisaku           #+#    #+#             */
/*   Updated: 2024/11/13 16:32:46 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Include negative sign - No null-terminated included
static int	get_num_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		len++;
	while (0 != nbr)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

static int	get_absolute(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*n_str;
	int		n_len;

	n_len = get_num_len(n);
	n_str = (char *)malloc((n_len + 1) * sizeof(char));
	if (n_str == NULL)
		return (NULL);
	if (n == 0)
		n_str[0] = '0';
	if (n < 0)
		n_str[0] = '-';
	n_str[n_len] = '\0';
	n_len--;
	while (n != 0)
	{
		n_str[n_len] = get_absolute(n % 10) + '0';
		n /= 10;
		n_len--;
	}
	return (n_str);
}
