#include <stddef.h> //for size_t,
#include <stdlib.h> //for malloc,
#include "../../libft/libft.h"
#include "../../include/utils.h"

char *ft_strndup(const char *s, size_t n)
{
    char *res;
	res = malloc(n + 1);
    if (!res)
        return NULL;
    ft_memcpy(res, s, n);
    res[n] = '\0';
    return res;
}
