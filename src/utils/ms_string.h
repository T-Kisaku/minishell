#ifndef MS_STRING_H

#define MS_STRING_H

#include <stddef.h>

int ms_strcmp(const char s1[], const char s2[]);
int ms_isspace(int c);
char *ms_strndup(const char *s, size_t n);

void *ms_strreduce(char const *s, void *init,
                   void *(*f)(unsigned int, char, void *));

#endif // !MS_STRING_H
