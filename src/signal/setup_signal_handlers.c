#include <minishell.h>
#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>

int setup_signal_handlers(void);
static void handle_sigint(int sig);

int setup_signal_handlers(void) {
  struct sigaction sa;

  sa.sa_handler = handle_sigint;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    perror("sigaction SIGINT");
    return (1);
  }
  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGQUIT, &sa, NULL) == -1) {
    perror("sigaction SIGQUIT");
    return (1);
  }
  return (0);
}

// SIGINT(Ctrl + c)
static void handle_sigint(int sig) {
  (void)sig;
  write(1, "\n", 1);      // 改行
  rl_on_new_line();       // readlineの内部状態を新しい行に
  rl_replace_line("", 0); // 入力行を空に
  rl_redisplay();         // プロンプトを再描画
}
