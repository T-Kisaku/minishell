#include "testdata.h"
#include "ast.h"
#include "token.h"
void free_testdata(t_testdata *d) {
  lstclear_token(&d->token_list);
  lstclear_and_or
(&d->ast);
}
