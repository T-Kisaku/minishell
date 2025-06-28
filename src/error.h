/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:54 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MS_ERROR_H
#define MS_ERROR_H

#include <stdbool.h>

#define ERR_MSG_MINISHEL "minishell: "
#define ERR_MSG_WRITE ERR_MSG_MINISHEL "write"
#define ERR_MSG_MALLOC ERR_MSG_MINISHEL "malloc"
#define ERR_MSG_EXECVP ERR_MSG_MINISHEL "execvp"
#define ERR_MSG_PWD ERR_MSG_MINISHEL "pwd"
#define ERR_MSG_DEV                                                            \
  ERR_MSG_MINISHEL "minishell's program is bad, not your fault👍"

typedef struct s_error {
  int exit_code;
  char *msg;
} t_error;

t_error *new_error(int exit_code, const char *msg);
void del_error(t_error *error);
bool is_error(t_error *error);

#endif // !MS_ERROR_H
