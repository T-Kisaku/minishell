#include "ast.h"
#include "minishell.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////
// This functions are for testing //
////////////////////////////////////

static int cmp_argv(char **a1, char **a2) {
  size_t i;

  if (a1 == NULL && a2 == NULL)
    return 1;
  if (a1 == NULL || a2 == NULL)
    return 0;

  for (i = 0; a1[i] && a2[i]; ++i) {
    if (strcmp(a1[i], a2[i]) != 0)
      return 0;
  }
  return (a1[i] == NULL && a2[i] == NULL);
}

static int cmp_redirects(const t_redirect *r1, const t_redirect *r2) {
  for (; r1 && r2; r1 = r1->next, r2 = r2->next) {
    if (strcmp(r1->op, r2->op) != 0)
      return 0;
    if (strcmp(r1->file, r2->file) != 0)
      return 0;
  }
  // 両方とも同じ長さか
  return (r1 == NULL && r2 == NULL);
}

int compare_ast(const t_ast *a, const t_ast *b) {
  if (a == NULL && b == NULL)
    return 1;
  if (a == NULL || b == NULL)
    return 0;

  // 1) ノード種別が同じか
  if (a->type != b->type)
    return 0;

  // 2) argv（コマンド＋引数）が同じか
  if (!cmp_argv(a->argv, b->argv))
    return 0;

  // 3) リダイレクトリストが同じか
  if (!cmp_redirects(a->redirects, b->redirects))
    return 0;

  // 4) 左右の子ノードを再帰的に比較
  if (!compare_ast(a->left, b->left))
    return 0;
  if (!compare_ast(a->right, b->right))
    return 0;

  return 1;
}
static void print_tokens(char **tokens) {
  printf("PASSED TOKENS: {");
  while (*tokens != NULL) {
    printf("\"%s\", ", *tokens);
    tokens++;
  }
  printf(" NULL}\n");
}

void test(char *tokens[], t_ast *expected, t_ast *actual) {
  int is_same = compare_ast(expected, actual);
  free_ast(actual);
  assert(is_same);
  print_tokens(tokens);
}

////////////////////////
// Content of testing //
////////////////////////

void test_normal_cmd() {
  char *tokens[] = {"ls", "-l", "/home", NULL};
  t_ast expected = (t_ast){.type = NODE_CMD,
                           .argv = tokens,
                           .redirects = NULL,
                           .left = NULL,
                           .right = NULL};
  t_ast *actual = parse_tokens(tokens);
  test(tokens, &expected, actual);
}

void test_pipe() {
  char *tokens[] = {"cat", "file.txt", "|", "grep", "hello", NULL};
  test(tokens,
       &(t_ast){.type = NODE_PIPE,
                .argv = NULL,
                .redirects = NULL,
                .left = &(t_ast){.type = NODE_CMD,
                                 .argv = (char *[]){"cat", "file.txt", NULL},
                                 .redirects = NULL,
                                 .left = NULL,
                                 .right = NULL},
                .right = &(t_ast){.type = NODE_CMD,
                                  .argv = (char *[]){"grep", "hello", NULL},
                                  .redirects = NULL,
                                  .left = NULL,
                                  .right = NULL}},
       parse_tokens(tokens));
}

void test_redirection() {
  char *tokens[] = {"echo", "hello", ">", "out.txt", NULL};
  test(tokens,
       &(t_ast){.type = NODE_CMD,
                .argv = (char *[]){"echo", "hello", NULL},
                .redirects =
                    &(t_redirect){.op = ">", .file = "out.txt", .next = NULL},
                .left = NULL,
                .right = NULL},
       parse_tokens(tokens));
}

void test_subshell_and() {
  char *tokens[] = {"(", "ls", "|",    "grep", "txt",
                    ")", "&&", "echo", "done", NULL};
  test(tokens,
       &(t_ast){.type = NODE_AND,
                .argv = NULL,
                .redirects = NULL,
                .left =
                    &(t_ast){.type = NODE_SUBSHELL,
                             .argv = NULL,
                             .redirects = NULL,
                             .left = &(t_ast){.type = NODE_PIPE,
                                              .argv = NULL,
                                              .redirects = NULL,
                                              .left = &(t_ast){.type = NODE_CMD,
                                                               .argv =
                                                                   (char *[]){
                                                                       "ls",
                                                                       NULL},
                                                               .redirects = NULL,
                                                               .left = NULL,
                                                               .right = NULL},
                                              .right = &(t_ast){.type =
                                                                    NODE_CMD,
                                                                .argv = (char
                                                                             *[]){"grep",
                                                                                  "txt", NULL},
                                                                .redirects = NULL,
                                                                .left = NULL,
                                                                .right = NULL}},
                             .right = NULL},
                .right = &(t_ast){.type = NODE_CMD,
                                  .argv = (char *[]){"echo", "done", NULL},
                                  .redirects = NULL,
                                  .left = NULL,
                                  .right = NULL}},
       parse_tokens(tokens));
}

#include <stdio.h>
int main() {
  test_normal_cmd();
  test_pipe();
  test_redirection();
  /* test_subshell_and(); */ // Bonusの範囲
  return (0);
}
