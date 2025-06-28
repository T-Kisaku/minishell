#include <stdlib.h>
#include "libft.h"
void *ft_realloc(void *ptr, size_t new_size) {
  void *new_ptr;
  size_t copy_size;
  if (ptr == NULL)
    return malloc(new_size);

  if (new_size == 0) {
    free(ptr);
    return NULL;
  }
  new_ptr = malloc(new_size);
  if (new_ptr == NULL)
    return NULL;

  copy_size = new_size;
  ft_memcpy(new_ptr, ptr, copy_size);
  free(ptr);

  return new_ptr;
}
