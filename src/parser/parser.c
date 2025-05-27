#include "ast.h"
#include "libft.h"
#include "minishell.h"
#include "ms_string.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * <command>    ::= <simple_command> ( "|" <command> )?
 * <simple_command> ::= WORD* <redirect>*
 * <redirect>   ::= ("<" | ">" | "<<" | ">>") WORD
 *
 * subshell, &&, ||は実装していない
 */

// TODO: temporary
#define MAX_ARGC 64

// 単純コマンド＋リダイレクトをパース
t_ast *parse_simple_command(char *tokens[], int *pos) {
  // argv を一時的に確保
  char **argv = malloc(sizeof(char *) * MAX_ARGC);
  int argc = 0;
  t_redirect *redirs = NULL;

  // WORD が続く限り argv に追加
  while (!is_end(tokens, *pos) && ms_strcmp(peek(tokens, *pos), "|") != 0 &&
         ms_strcmp(peek(tokens, *pos), "<") &&
         ms_strcmp(peek(tokens, *pos), ">") &&
         ms_strcmp(peek(tokens, *pos), "<<") &&
         ms_strcmp(peek(tokens, *pos), ">>")) {
    argv[argc++] = ft_strdup(eat(tokens, pos));
  }
  argv[argc] = NULL;

  // リダイレクト処理
  while (!is_end(tokens, *pos) && (ms_strcmp(peek(tokens, *pos), "<") == 0 ||
                                   ms_strcmp(peek(tokens, *pos), ">") == 0 ||
                                   ms_strcmp(peek(tokens, *pos), "<<") == 0 ||
                                   ms_strcmp(peek(tokens, *pos), ">>") == 0)) {

    char *op = eat(tokens, pos); // "<" or ">" etc.
    if (is_end(tokens, *pos))
      error();
    // TODO: error message
    /* error("リダイレクトの後にファイル名がありません"); */
    char *file = eat(tokens, pos); // ファイル名
    t_redirect *r = new_redirect(op, file);
    // リストの先頭にプッシュ
    r->next = redirs;
    redirs = r;
  }

  return new_cmd_node(argv, redirs);
}

// パイプ込みでコマンド全体をパース
t_ast *parse_command(char *tokens[], int *pos) {
  t_ast *left = parse_simple_command(tokens, pos);

  if (!is_end(tokens, *pos) && ms_strcmp(peek(tokens, *pos), "|") == 0) {
    eat(tokens, pos); // "|"
    t_ast *right = parse_command(tokens, pos);
    return new_pipe_node(left, right);
  }

  return left;
}

t_ast *parse_tokens(char *tokens[]) {
  int pos = 0;
  char **global_tokens = tokens;
  return parse_command(global_tokens, &pos);
}
