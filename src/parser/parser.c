#include "ast.h"
#include "minishell.h"
#include "token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * <command>    ::= <simple_command> ( "|" <command> )?
 * <simple_command> ::= WORD* <redirect>*
 * <redirect>   ::= ("<" | ">" | "<<" | ">>") WORD
 */

// TODO: temporary
#define MAX_ARGC 64
// TODO: replace strcmp with our ms_strcmp
/* t_ast *parser(char *tokens[]) {} */

// 単純コマンド＋リダイレクトをパース
t_ast *parse_simple_command(char *tokens[], int pos) {
  // argv を一時的に確保
  char **argv = malloc(sizeof(char *) * MAX_ARGC);
  int argc = 0;
  t_redirect *redirs = NULL;

  // WORD が続く限り argv に追加
  while (!is_end(tokens, pos) && strcmp(peek(tokens, pos), "|") != 0 &&
         strcmp(peek(tokens, pos), "<") && strcmp(peek(tokens, pos), ">") &&
         strcmp(peek(tokens, pos), "<<") && strcmp(peek(tokens, pos), ">>")) {
    argv[argc++] = eat(tokens, &pos);
  }
  argv[argc] = NULL;

  // リダイレクト処理
  while (!is_end(tokens, pos) && (strcmp(peek(tokens, pos), "<") == 0 ||
                                  strcmp(peek(tokens, pos), ">") == 0 ||
                                  strcmp(peek(tokens, pos), "<<") == 0 ||
                                  strcmp(peek(tokens, pos), ">>") == 0)) {

    char *op = eat(tokens, &pos); // "<" or ">" etc.
    if (is_end(tokens, pos))
      error();
    // TODO: error message
    /* error("リダイレクトの後にファイル名がありません"); */
    char *file = eat(tokens, &pos); // ファイル名
    t_redirect *r = new_redirect(op, file);
    // リストの先頭にプッシュ
    r->next = redirs;
    redirs = r;
  }

  return new_cmd_node(argv, redirs);
}

// パイプ込みでコマンド全体をパース
t_ast *parse_command(char *tokens[], int pos) {
  t_ast *left = parse_simple_command(tokens, pos);

  if (!is_end(tokens, pos) && strcmp(peek(tokens, pos), "|") == 0) {
    eat(tokens, &pos); // "|"
    t_ast *right = parse_command(tokens, pos);
    return new_pipe_node(left, right);
  }

  return left;
}

t_ast *parse_tokens(char *tokens[]) {
  int pos = 0;
  return parse_command(tokens, pos);
}
