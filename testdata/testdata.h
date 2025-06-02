#ifndef TESTDATA_H
#define TESTDATA_H

#include "ast.h"

typedef struct s_token {
  char *token;
  int flags; // NOT DECIDED SO JUST PUT 0
} t_token;
typedef struct s_token_list {
  struct t_token_list *next;
  t_token *token;
} t_token_list;

typedef struct s_testdata {
  char *input;
  t_token_list token_list;
  t_ast ast;
} t_testdata;

t_testdata ls();

#endif // !TESTDATA_H
