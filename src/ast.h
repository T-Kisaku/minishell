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
#define AST_H

#include <stddef.h>
#include <stdbool.h>
#include "libft.h"
#include "token.h"

/******************************************************************************/
/* list                                                                       */
/******************************************************************************/

typedef t_list t_ast; // content = t_and_or*;

/******************************************************************************/
/* and_or                                                                     */
/******************************************************************************/
typedef struct s_pipeline t_pipeline;
typedef enum e_andor_op { OP_NONE, OP_AND, OP_OR } t_andor_op;
typedef struct s_and_or {
  t_pipeline *pipeline;
  t_andor_op op_next;
} t_and_or;

// t_list *lstnew_and_or(int type, const char *target);
t_and_or *lstget_and_or(t_list *node);
// void del_and_or(void *ptr);

/******************************************************************************/
/* pipeline                                                                   */
/******************************************************************************/

typedef struct s_pipeline {
  t_list *command_list; // content = t_command*
} t_pipeline;

/******************************************************************************/
/* command                                                                    */
/******************************************************************************/
typedef enum e_cmd_type { CMD_SIMPLE, CMD_SUBSHELL } t_cmd_type;

typedef union {
  struct {
    t_list *token_list; // When you pass this to Executor, free this.
    char **argv;        // Malloc from token_list
    int argc;
  } simple;

  struct {
    t_list *and_or_list; // content = t_and_or*
  } subshell;
} u_command;

typedef struct s_command {
  t_list *redir_list; // content = t_redir*

  t_cmd_type type;
  t_list *redir_list; // content = t_redir*

  u_command u;
} t_command;

// t_list *lstnew_command(int type, const char *target);
t_command *lstget_command(t_list *node);
// void del_command(void *ptr);

/******************************************************************************/
/* redirection                                                                */
/******************************************************************************/

typedef enum e_redir_type {
  REDIR_INPUT,
  REDIR_OUTPUT,
  REDIR_HERE_DOC,
  REDIR_APPEND
} t_redir_type;

typedef struct s_redir_target {
  bool is_direct_to_fd; // whether fd is set without char *target
  int fd;               // set -1 as initial value
  char *filename;       // filename is going to be assigned when it's expander!
  t_token_content *filename_token;
} t_redir_target;

typedef struct s_redir {
  t_redir_type type;
  t_redir_target to;
  t_redir_target from;
} t_redir;

t_redir *new_redir();
t_redir *lstget_redir(t_list *node);
void del_redir(void *ptr);

t_list *lstnew_redir(int type, const t_list *token);
t_list *new_fd_redir_lst(int type, int fd);
t_redir *lstget_redir(t_list *node);
void del_redir(void *ptr);

#endif /* AST_H */