#include <stdlib.h> //malloc,
# include <stddef.h> //size_t
#include "libft.h" //ft_memcpy,

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
