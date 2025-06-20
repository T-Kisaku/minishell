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

t_and_or *lstget_and_or(t_list *node);
void del_and_or(void *content);
void lstclear_and_or(t_ast **ast);
t_and_or *new_and_or(t_andor_op andor_op);
t_list *lstnew_and_or(t_andor_op andor_op);
t_list *lstadd_back_and_or(t_list **and_or_list_ptr, t_andor_op andor_op);
#define free_ast lstclear_and_or

/******************************************************************************/
/* pipeline                                                                   */
/******************************************************************************/

typedef struct s_pipeline {
  t_list *command_list; // content = t_command*
} t_pipeline;

t_pipeline *new_pipeline();
void del_pipeline(t_pipeline *pipe);

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

  u_command u;
} t_command;

void lstclear_cmd(t_list **command_list);
t_command *lstget_command(t_list *node);
void del_command(void *content);

t_command *new_command(t_cmd_type cmd_type);
t_list *lstnew_command(t_cmd_type cmd_type);
t_list *lstadd_back_command(t_list **cmd_list_ptr, t_cmd_type cmd_type);

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
  t_token *filename_token;
} t_redir_target;

typedef struct s_redir {
  t_redir_type type;
  t_redir_target to_be_redirected;
  t_redir_target redirect_source;
} t_redir;

t_redir *new_redir(void);
t_list *lstnew_redir(t_redir_type redir_type, t_token *filename_token);
t_list *lstadd_back_redir(t_list **redir_list_ptr, t_redir_type redir_type,
                          t_token *filename_token);
t_redir *lstget_redir(t_list *node);
t_redir_type get_redir_type(t_token_type token_type);
void del_redir(void *ptr);
void clear_redir_list(t_list **head);

#endif /* AST_H */
