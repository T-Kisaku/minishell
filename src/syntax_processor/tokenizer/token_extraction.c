#include <stdio.h>
#include "libft.h"
#include "exit_status.h"
#include "error.h"
#include "token.h"
#include "syntax_processor/tokenizer.h"

t_error *extract_and_add_token(t_token_context *ctx, t_token_type type) {
  char *value;
  size_t len;

  len = ctx->cur_str - ctx->start_str;
  value = ft_substr(ctx->start_str, 0, len);
  // TODO:
  if (!value)
    return new_error(EXIT_INTERNAL_ERR, "use strerror to make propper erro");

  if (lstadd_back_token(ctx->head, value, type) == NULL) {
    free(value);
    return new_error(EXIT_INTERNAL_ERR, "TODO: propper erro");
  }
  free(value);
  ctx->start_str = ctx->cur_str;
  return (NULL);
}
