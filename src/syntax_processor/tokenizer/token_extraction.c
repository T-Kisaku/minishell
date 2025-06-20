#include <stdio.h>
#include "libft.h"
#include "exit_status.h"
#include "error.h"
#include "token.h"
#include "syntax_processor/tokenizer.h"

int extract_and_add_token(t_token_context *ctx, t_token_type type) {
  char *value;
  size_t len;

  len = ctx->cur_str - ctx->start_str;
  value = ft_substr(ctx->start_str, 0, len);
  if (!value) {
    perror(ERR_MSG_MALLOC);
    return (EXIT_INTERNAL_ERR);
  }

  if (lstadd_back_token(ctx->head, value, type) == NULL) {
    free(value);
    return (EXIT_INTERNAL_ERR);
  }
  free(value);
  ctx->start_str = ctx->cur_str;
  return (EXIT_OK);
}
