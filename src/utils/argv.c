/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:56 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:56 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

// TODO: argv -> str_array
// TODO: NULL terminate
void free_argv(char ***argv, int num) {
  int i;

  if (!argv || !*argv)
    return;
  i = 0;
  if (num == INT_MAX)
    while ((*argv)[i]) {
      free((*argv)[i]);
      (*argv)[i] = NULL;
      i++;
    }
  else {
    while (i < num) {
      free((*argv)[i]);
      (*argv)[i] = NULL;
      i++;
    }
  }
  free(*argv);
  *argv = NULL;
}

void free_argv_null(char ***argv) {
  int i;

  if (!argv || !*argv)
    return;

  i = 0;
  while ((*argv)[i]) {
    free((*argv)[i]);
    i++;
  }
  free(*argv);
  *argv = NULL;
}

char **copy_argv(char **argv) {
  int i = 0;
  while (argv[i])
    i++;

  char **copy = malloc(sizeof(char *) * (i + 1));
  for (int j = 0; j < i; j++)
    copy[j] = ft_strdup(argv[j]);
  copy[i] = NULL;
  return copy;
}
