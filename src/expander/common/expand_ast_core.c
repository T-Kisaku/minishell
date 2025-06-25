#include "expander.h"

static t_error *
expand_ast_core_core_core(t_expansion_context *ctx,
                                 t_error *(*func)(t_expansion_context *),
                                 e_expander_mode mode);

t_error *expand_ast_core_core(t_expansion_context *ctx,
                                     e_expander_mode mode) {
  t_error *error;
  error = NULL;
  if (ctx->cur_dollar_type == DOLLAR_SPECIAL) {
    error = expand_ast_core_core_core(ctx, expand_special, mode);
    if (is_error(error))
      return error;
  } else if (ctx->cur_dollar_type == DOLLAR_VARIABLE) {
    error = expand_ast_core_core_core(ctx, expand_variable, mode);
    if (is_error(error))
      return error;
  } else if (ctx->cur_dollar_type == DOLLAR_LITERAL && mode == MODE_SET_VALUE)
    copy_and_advance(ctx, --ctx->cur_pos, 1);
  return error;
}

static t_error *
expand_ast_core_core_core(t_expansion_context *ctx,
                                 t_error *(*func)(t_expansion_context *),
                                 e_expander_mode mode) {
  int len;
  t_error *error;

  error = func(ctx);
  if (is_error(error)) {
    free(ctx->variable);
    ctx->variable = NULL;
    return error;
  }
  len = ft_strlen(ctx->variable);
  if (mode == MODE_SET_VALUE && len > 0)
    ft_memcpy(&ctx->output[ctx->index], ctx->variable, len);
  ctx->index += len;
  free(ctx->variable);
  ctx->variable = NULL;
  return NULL;
}
