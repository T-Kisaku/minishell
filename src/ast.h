/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/30 09:24:45 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * # EBNF
 *
 * <command_line>      ::= <list> <EOF>
 *
 * <list>              ::= <and_or> { ";" <and_or> }
 *
 * <and_or>            ::= <pipeline> { ( "&&" | "||" ) <pipeline> }
 *
 * <pipeline>          ::= <command> { "|" <command> }
 *
 * <command>           ::= <simple_command>
 *                       | <subshell>
 *
 * <simple_command>    ::= <argument_list> [ <redirection_list> ]
 *
 * <subshell>          ::= "(" <list> ")" [ <redirection_list> ]
 *
 * <argument_list>     ::= <argument> { <whitespace> <argument> }
 * <argument>          ::= <word>
 *
 * <redirection_list>  ::= { <whitespace> <redirection> }
 *
 * <redirection>       ::= "<"   <redirect_target>
 *                       | ">"   <redirect_target>
 *                       | "<<"  <redirect_token>
 *                       | ">>"  <redirect_target>
 *
 * <redirect_target>   ::= <word>
 * <redirect_token>    ::= <word>
 *
 * <word>              ::= {
 *                            <unquoted_char> |
 *                            <single_quoted> |
 *                            <double_quoted> |
 *                            <variable>
 *                         }
 *
 */

#ifndef AST_H
# define AST_H

# include "token.h"
# include <stdbool.h>
# include <stddef.h>

/******************************************************************************/
/*                              Redirection                                   */
/******************************************************************************/

/**
 * @brief Redirection type
 */
typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_HERE_DOC,
	REDIR_APPEND
}						t_redir_type;

/**
 * @brief Redirection target
 */
typedef struct s_redir_target
{
	/** Whether fd is set without char *filename */
	bool				is_direct_to_fd;
	/** File descriptor, set -1 as initial value */
	int					fd;
	/** Assigned when expanded */
	char				*filename;
	/** Token for filename (before expansion) */
	t_token				*filename_token;
}						t_redir_target;

/**
 * @brief Redirection
 *
 * The redirection concept follows the form:
 * @code
 * echo [to_be_redirected] > [redirect_source]
 * cat  [to_be_redirected] < [redirect_source]
 * @endcode
 */
typedef struct s_redir
{
	/** Redirection type */
	t_redir_type		type;
	/** The source to be redirected */
	t_redir_target		to_be_redirected;
	/** The redirection destination */
	t_redir_target		redirect_source;
}						t_redir;

t_redir					*new_redir(void);
t_list					*lstnew_redir(t_redir_type redir_type,
							t_token *filename_token);
t_list					*lstadd_back_redir(t_list **redir_list_ptr,
							t_redir_type redir_type, t_token *filename_token);
t_redir					*lstget_redir(t_list *node);
t_redir_type			get_redir_type(t_token_type token_type);
void					del_redir(void *ptr);
void					clear_redir_list(t_list **head);

/******************************************************************************/
/*                              Command                                       */
/******************************************************************************/

/**
 * @brief Command type
 */
typedef enum e_cmd_type
{
	CMD_SIMPLE,
	CMD_SUBSHELL
}						t_cmd_type;

/**
 * @brief Simple command structure
 */
typedef struct s_command_simple
{
	/** Token list, free after executor */
	t_list				*token_list;
	/** Argument vector */
	char				**argv;
	/** Argument count */
	int					argc;
}						t_command_simple;

/**
 * @brief Subshell command structure
 */
typedef struct s_command_subshell
{
	/** List of and_or nodes (content = t_and_or*) */
	t_list				*and_or_list;
}						t_command_subshell;

/**
 * @brief Union for command
 */
typedef union u_command
{
	t_command_simple	simple;
	t_command_subshell	subshell;
}						t_command_u;

/**
 * @brief Command
 */
typedef struct s_command
{
	/** Redirection list (content = t_redir*) */
	t_list				*redir_list;
	/** Command type */
	t_cmd_type			type;
	/** Command data */
	t_command_u			u;
}						t_command;

void					lstclear_cmd(t_list **command_list);
t_command				*lstget_command(t_list *node);
void					del_command(void *content);
t_command				*new_command(t_cmd_type cmd_type);
t_list					*lstnew_command(t_cmd_type cmd_type);
t_list					*lstadd_back_command(t_list **cmd_list_ptr,
							t_cmd_type cmd_type);

/******************************************************************************/
/*                              Pipeline                                      */
/******************************************************************************/

/**
 * @brief Pipeline
 */
typedef struct s_pipeline
{
	/** Command list (content = t_command*) */
	t_list				*command_list;
}						t_pipeline;

t_pipeline				*new_pipeline(void);
void					del_pipeline(t_pipeline *pipe);

/******************************************************************************/
/*                              And-Or                                        */
/******************************************************************************/

/**
 * @brief And-Or operator type
 */
typedef enum e_andor_op
{
	OP_NONE,
	OP_AND,
	OP_OR
}						t_andor_op;

/**
 * @brief And-Or node
 */
typedef struct s_and_or
{
	/** Pipeline node */
	t_pipeline			*pipeline;
	/** Operator for the next pipeline */
	t_andor_op			op_next;
}						t_and_or;

t_and_or				*lstget_and_or(t_list *node);
void					del_and_or(void *content);
void					lstclear_and_or(t_list **ast);
t_and_or				*new_and_or(t_andor_op andor_op);
t_list					*lstnew_and_or(t_andor_op andor_op);
t_list					*lstadd_back_and_or(t_list **and_or_list_ptr,
							t_andor_op andor_op);

/******************************************************************************/
/*                              AST                                           */
/******************************************************************************/

typedef t_list			t_ast;

#endif /* AST_H */
