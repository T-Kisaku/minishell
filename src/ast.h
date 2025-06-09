
// TODO: delete comments
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
 * <word>              ::= { <unquoted_char> | <single_quoted> | <double_quoted>
 * | <variable> } (ここではパース時にすべて展開済み文字列とする)
 *
 */

#ifndef AST_H
#define AST_H

#include <stddef.h>
#include "token.h"

typedef enum e_redir_type {
  REDIR_INPUT,
  REDIR_OUTPUT,
  REDIR_HERE_DOC,
  REDIR_APPEND
} t_redir_type;

typedef struct s_redir {
  t_redir_type type;
  char *target;
} t_redir;

typedef enum e_cmd_type { CMD_SIMPLE, CMD_SUBSHELL } t_cmd_type;

typedef struct s_a_list t_a_list;

typedef struct s_command {	
  t_cmd_type type;
  t_redir *redirs;
  int redir_count;

  union {
    struct {
      t_token_list *token_list; // When you pass this to Executor, free this.
      char **argv;              // Malloc from token_list
      int argc;
    } simple;

    struct {
      t_a_list *list;
    } subshell;
  } u;
} t_command;

typedef struct s_pipeline {
  t_command *commands;
  int cmd_count;
} t_pipeline;

typedef enum e_andor_op { OP_NONE, OP_AND, OP_OR } t_andor_op;

typedef struct s_and_or {
  t_pipeline pipeline;
  t_andor_op op_next;
  struct s_and_or *next;
} t_and_or;

typedef struct s_a_list {
  t_and_or *first_and_or;
  struct s_a_list *next;
} t_a_list;

typedef t_a_list t_ast;

#endif /* AST_H */
