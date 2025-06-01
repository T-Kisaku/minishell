
// TODO: delete comments
/*
 * Minimal C 構造体定義 (Executor 用に必要最低限)：
 *
 * 拡張された EBNF:
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
 * 以下の構造体は、Executor（ミニシェルの実行部）で必要な最小限の情報を保持する。
 */

#ifndef AST_H
#define AST_H

#include <stddef.h>

/*-------------------------------------------------------
 * 1. リダイレクションの種類
 *-------------------------------------------------------*/
typedef enum e_redir_type {
  REDIR_INPUT,    /* "<"   */
  REDIR_OUTPUT,   /* ">"   */
  REDIR_HERE_DOC, /* "<<"  */
  REDIR_APPEND    /* ">>"  */
} t_redir_type;

/*
 * t_redir:
 *   - type   : リダイレクト演算子の種類 (REDIR_INPUT, REDIR_OUTPUT, ...)
 *   - target : リダイレクト先の文字列
 * (ファイル名、またはヒアドキュメントのデリミタ)
 */
typedef struct s_redir {
  t_redir_type type;
  char *target; /* 例: "out.txt", "EOF" など */
} t_redir;

/*-------------------------------------------------------
 * 2. コマンド (単純コマンド OR サブシェル)
 *-------------------------------------------------------*/
typedef enum e_cmd_type {
  CMD_SIMPLE,  /* simple_command */
  CMD_SUBSHELL /* subshell */
} t_cmd_type;

/*
 * t_command:
 *   - type       : CMD_SIMPLE または CMD_SUBSHELL
 *   - redirs     : リダイレクト配列 (NULL ならリダイレクションなし)
 *   - redir_count: redirs 配列の要素数
 *
 *   - simple:
 *       - argv : NULL 終端の文字列配列 (例: {"ls", "-l", NULL})
 *       - argc : 引数の個数 (NULL を除いた数)
 *
 *   - subshell:
 *       - list : サブシェル内の <list> を指すポインタ
 */
typedef struct s_list t_list; /* 後述 */

typedef struct s_command {
  t_cmd_type type;
  /* <redirection_list> 共通部分 */
  t_redir *redirs; /* 動的に確保されたリダイレクト情報の配列 */
  int redir_count; /* redirs 配列の要素数 */

  union {
    struct {
      char **argv; /* NULL 終端文字列配列 (展開済みの単語リスト) */
      int argc;    /* argv の要素数 (NULL を除く) */
    } simple;

    struct {
      t_list *list; /* "(" <list> ")" の内部を指す */
    } subshell;
  } u;
} t_command;

/*-------------------------------------------------------
 * 3. パイプライン (複数のコマンドを "|" でつなぐ)
 *-------------------------------------------------------*/
/*
 * t_pipeline:
 *   - commands  : t_command の配列
 *   - cmd_count : 配列の要素数 (パイプでつながれたコマンド数)
 *
 * grammar:
 *   <pipeline> ::= <command> { "|" <command> }
 */
typedef struct s_pipeline {
  t_command *
      commands; /* 動的配列 (例: commands[0] = cmd1, commands[1] = cmd2, ...) */
  int cmd_count; /* commands の要素数 */
} t_pipeline;

/*-------------------------------------------------------
 * 4. AND/OR リスト (pipeline を && または || でつなぐ)
 *-------------------------------------------------------*/
typedef enum e_andor_op {
  OP_NONE, /* 最後の要素、または単独の pipeline の場合 */
  OP_AND,  /* "&&" */
  OP_OR    /* "||" */
} t_andor_op;

/*
 * t_and_or:
 *   - pipeline : 単一のパイプライン
 *   - op_next  : この pipeline の評価結果に応じて次の pipeline
 * を実行するかどうかを示す (OP_AND: 成功したら次へ, OP_OR: 失敗したら次へ,
 * OP_NONE: 次はない)
 *   - next     : 次の t_and_or 要素 (OP_NONE のときは NULL)
 *
 * grammar:
 *   <and_or> ::= <pipeline> { ( "&&" | "||" ) <pipeline> }
 */
typedef struct s_and_or {
  t_pipeline pipeline;
  t_andor_op op_next;
  struct s_and_or *next; /* 次の and_or 要素へのポインタ */
} t_and_or;

/*-------------------------------------------------------
 * 5. リスト (and_or を ";" で区切る)
 *-------------------------------------------------------*/
/*
 * t_list:
 *   - first_and_or : この要素の and_or チェーンの先頭
 *   - next         : ";" の後に続く別の and_or の先頭
 *
 * grammar:
 *   <list> ::= <and_or> { ";" <and_or> }
 *
 * 例: "cmd1 && cmd2 || cmd3 ; cmd4 | cmd5" は
 *   t_list node1: first_and_or → (  pipeline(cmd1) --[OP_AND]→ pipeline(cmd2)
 * --[OP_OR]→ pipeline(cmd3) ), next → node2 t_list node2: first_and_or → (
 * pipeline(cmd4) --[OP_NONE]→ pipeline(cmd5) ), next → NULL
 */
typedef struct s_list {
  t_and_or *first_and_or; /* このセミコロン区切り要素の and_or チェーン */
  struct s_list *next;    /* 次の ";" 区切り要素 */
} t_list;

typedef t_list t_ast;

#endif /* AST_H */
