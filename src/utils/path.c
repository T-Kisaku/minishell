#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// TODO: refactor path related funcs, is_cd_target_valid, get_command_path at
// executor
int is_cd_target_valid(const char *path) {
  struct stat st;

  if (access(path, F_OK) != 0) {
    fprintf(stderr, "cd: %s: No such file or directory\n", path);
    return 0;
  }
  if (stat(path, &st) != 0) {
    fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
    return 0;
  }
  if (!S_ISDIR(st.st_mode)) {
    fprintf(stderr, "cd: %s: Not a directory\n", path);
    return 0;
  }
  if (access(path, X_OK) != 0) {
    fprintf(stderr, "cd: %s: Permission denied\n", path);
    return 0;
  }
  return 1; // cd可能
}
