#ifndef ARGV_H
#define ARGV_H

void free_argv(char ***argv, int num);
void free_argv_null(char ***argv);
char **copy_argv(char **argv);
void str_arr_iter(char **arr, void (*f)(char **, int));

void set_env(t_list *env_list, const char *key, const char *value);
char **remove_str(char **str_arr, const char *key);
#endif // !ARGV_H
