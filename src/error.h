
#ifndef MS_ERROR_H
#define MS_ERROR_H

#define ERR_MSG_MINISHEL "minishell: "
#define ERR_MSG_WRITE ERR_MSG_MINISHEL "write"
#define ERR_MSG_MALLOC ERR_MSG_MINISHEL "malloc"
#define ERR_MSG_EXECVP ERR_MSG_MINISHEL "execvp"
#define ERR_MSG_PWD ERR_MSG_MINISHEL "pwd"
#define ERR_MSG_DEV                                                            \
  ERR_MSG_MINISHEL "minishell's program is bad, not your fault👍"

int user_error(char *msg);
void dev_error();

typedef struct s_err {
  int exit_code;
  char *msg;
} t_err;

#endif // !MS_ERROR_H
