#include <unistd.h> // access, getenv
#include "libft.h"
#include "ast.h"
#include "utils/argv.h"
#include "utils/env.h"

#include <stdio.h>
static char *get_command_path(const char *cmd, t_list *env_list) {
  char **paths;
  char *path_env;
  char *full_path;
  int i;
  t_error *error;
  error = NULL;
  if (!cmd || !*cmd)
    return (NULL);

  // 1. もし cmd が '/' を含むなら、直接実行可能か確認
  if (ft_strchr(cmd, '/'))
    return (access(cmd, X_OK) == 0 ? ft_strdup(cmd) : NULL);

  // 2. PATH 環境変数を取得
  error = ms_getenv("PATH", &path_env, env_list);
  if(is_error(error)) {
	del_error(error);
	return NULL;
  }
  if (!path_env)
    return (NULL);

  // 3. PATH を ':' で分割
  paths = ft_split(path_env, ':');
  free(path_env);
  if (!paths)
    return (NULL);

  i = 0;
  while (paths[i]) {
    char *temp = ft_strjoin(paths[i], "/");
    full_path = ft_strjoin(temp, cmd);
    free(temp);
    if (access(full_path, X_OK) == 0) {
      free_argv_null(&paths);
      return (full_path);
    }
    free(full_path);
    i++;
  }

  free_argv_null(&paths);
  return (NULL);
}

char *set_cmd_path(t_command *cmd, t_list *env_list) {
  char *full_path;
  full_path = get_command_path(cmd->u.simple.argv[0], env_list);
  if (!full_path)
    return NULL;

  free(cmd->u.simple.argv[0]);
  cmd->u.simple.argv[0] = full_path;
  return full_path;
}
