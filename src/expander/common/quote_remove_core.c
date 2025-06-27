#include <stddef.h>
#include "libft.h"
#include "token.h"
#include "error.h"
#include "exit_status.h"

t_error *quote_remove_core(t_token *content);
static int count_quotes(char *s);
static t_error *copy_without_quotes(char *dst, const char *src);

t_error *quote_remove_core(t_token *content) {
  size_t value_len;
  int quote_count;
  char *tmp;
  t_error *error;
  error = NULL;

  value_len = ft_strlen(content->value);
  quote_count = count_quotes(content->value);
  tmp = malloc(sizeof(char) * (value_len - quote_count + 1));
  if (!tmp)
    return new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO");
  error = copy_without_quotes(tmp, content->value);
  if (is_error(error))
  {free(tmp);
    return error;}
  free(content->value);
  content->value = tmp;
  return error;
}
static int count_quotes(char *s) {
  int quote_count;

  if (!s)
    return (-1);
  quote_count = 0;
  while (*s) {
    if (*s == '\'' || *s == '"')
      quote_count++;
    s++;
  }
  return (quote_count);
}

static t_error *copy_without_quotes(char *dst, const char *src) {
  if (!dst || !src)
    return new_error(EXIT_INTERNAL_ERR, "it's not propper args");
  while (*src) {
    if (*src != '\'' && *src != '"') {
      *dst = *src;
      dst++;
    }
    src++;
  }
  *dst = '\0';
  return NULL;
}
