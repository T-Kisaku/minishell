/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:45:57 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/16 15:08:00 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

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

int ms_isspace(int c) {
  if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
    return (1);
  else
    return (0);
}

char *ms_strndup(const char *s, size_t n) {
  char *res;
  res = malloc(n + 1);
  if (!res)
    return NULL;
  ft_memcpy(res, s, n);
  res[n] = '\0';
  return res;
}
