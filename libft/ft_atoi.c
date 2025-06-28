/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:55:11 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/28 10:13:09 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal(const char *nptr, int i, int sign)
{
	int	num;
	int	prev_num;

	num = 0;
	while (ft_isdigit(nptr[i]))
	{
		prev_num = num;
		num = (num * 10) + nptr[i] - '0';
		if ((num - (nptr[i] - '0')) / 10 != prev_num)
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		i++;
	}
	return ((int)(num * sign));
}

/*
 * 1. white spcaces
 * 2. signs
 * 3. numbers
 */
int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	return (cal(nptr, i, sign));
}

// #include <stdio.h>
// int	main(void)
// {
// 	// char *ascii = "2147483647"; // MAX_LONG
// 	// char *ascii = "10"; // MAX_LONG
// 	// char *ascii = "2147483648"; // MAX_LONG + 1
// 	// char *ascii = "4294967294"; // MAX_LONG * 2
// 	// char *ascii = "9223372036854775807"; // MAX_LLONG
// 	// char *ascii = "9223372036854775808"; // MAX_LLONG + 1
// 	//  int ft = ft_atoi(ascii);
// 	//  int std = atoi(ascii);
// 	// printf("ft_atoi: %d\n", ft);
// 	// printf("atoi: %d\n", std);
// 	// printf("diff: %d\n", ft - std);
// 	printf("diff: %d\n", atoi("-1"));
// 	printf("diff: %d\n", atoi("-+1"));
// 	printf("diff: %d\n", atoi("--1"));
// 	printf("diff: %d\n", atoi("+-+1"));
// 	return (EXIT_SUCCESS);
// }
