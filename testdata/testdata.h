#ifndef TESTDATA_H
#define TESTDATA_H

#include "ast.h"

typedef struct s_testdata {
  char *input;
  t_token_list token_list;
  t_ast ast;
} t_testdata;


t_testdata ls();
t_testdata echo_fire();
t_testdata ls_pipe_grep();
t_testdata ls_pipe_grep_pipe_wc();

#endif // !TESTDATA_H
