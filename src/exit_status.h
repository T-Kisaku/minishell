/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:54 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXIT_STATUS_H
#define MS_EXIT_STATUS_H

#define EXIT_OK 0            // Success
#define EXIT_INTERNAL_ERR 1  // Internal error (e.g., malloc failure)
#define EXIT_USER_ERR 2      // User error (e.g., input or syntax error)
#define EXIT_EOF 3           // in syntax_check , bad syntax error etc
#define EXIT_EXEC_FAIL 126   // Execution failure (e.g., permission denied)
#define EXIT_NOT_FOUND 127   // Command not found
#define EXIT_SIGNAL_BASE 128 // Exit caused by signal (add signal number)

#endif // !MS_EXIT_STATUS_H
