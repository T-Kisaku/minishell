/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:45:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/05/23 18:50:02 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int ms_strcmp(const char s1[], const char s2[]) {
  size_t i;
  const unsigned char *p1;
  const unsigned char *p2;

  p1 = (const unsigned char *)s1;
  p2 = (const unsigned char *)s2;
  i = 0;
  while (p1[i] || p2[i]) {
    if (p1[i] != p2[i])
      return (p1[i] - p2[i]);
    i++;
  }
  return (0);
}
