#include "token.h"
#include <stdbool.h>
#include <stdlib.h>

// TODO: think whether it's better to define as pointer for  pos
bool is_end(char *tokens[], int pos) { return tokens[pos] == NULL; }
char *peek(char *tokens[], int pos) { return tokens[pos]; }
char *eat(char *tokens[], int *pos) { return tokens[*pos++]; }
