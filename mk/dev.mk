PHONY_TARGETS += norm format stdheader dev install lsp-setup get-src-files set-src-files
check:
	@$(MAKE) check-norm
	@$(MAKE) check-undef-syms
	@$(MAKE) check-non-ascii

check-norm:
	@$(MAKE) print_running TARGET="norminette"
	@norminette $(SRCS) $(wildcard src/*.h) $(wildcard src/**/*.h) | grep -v "OK" || true
	@$(MAKE) norm -C $(LIBFTDIR)

check-non-ascii:
	@$(MAKE) print_running TARGET="ascii validation"
	@! grep -P "[^\x00-\x7F]" $(SRCS) $(wildcard src/*.h) $(wildcard src/**/*.h) \
		&& echo "All code are ascii!!!" \
		|| (echo "Non-ASCII characters found!" && false)

check-undef-syms:
	@$(MAKE) print_running TARGET="function validation"
	@$(MAKE) re > /dev/null
	@nm minishell | \
	awk '$$1 == "U" {print $$2}' | \
	cut -d'@' -f1 | \
	grep -Ev '^(__errno_location|__libc_start_main)$$' | \
	grep -Ev '^(readline|rl_clear_history|rl_on_new_line|rl_replace_line|rl_redisplay|add_history|printf|malloc|free|write|access|open|read|close|fork|wait|waitpid|wait3|wait4|signal|sigaction|sigemptyset|sigaddset|kill|exit|getcwd|chdir|stat|lstat|fstat|unlink|execve|dup|dup2|pipe|opendir|readdir|closedir|strerror|perror|isatty|ttyname|ttyslot|ioctl|getenv|tcsetattr|tcgetattr|tgetent|tgetflag|tgetnum|tgetstr|tgoto|tputs)$$' > unexpected_syms.txt; \
	if [ -s unexpected_syms.txt ]; then \
		echo "Unexpected undefined symbols found:"; \
		cat unexpected_syms.txt; \
	else \
		echo " All undefined symbols are allowed."; \
	fi

format:
	@c_formatter_42 $(SRCS) $(wildcard src/*.h) $(wildcard src/**/*.h)

stdheader:
	@stdheader $(SRCS) $(wildcard src/*.h) $(wildcard src/**/*.h)

dev:
	@$(MAKE) set-src-files
	@$(MAKE) install
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp minishell

INSTALL_DIR := $(HOME)/.local/bin
MINISHELL_EXEC := minishell
install:
	@$(MAKE)
	@echo "🔧 Installing minishell to $(INSTALL_DIR)..."

	# Create ~/.local/bin if it doesn't exist
	mkdir -p "$(INSTALL_DIR)"

	# Copy the minishell executable
	cp "$(MINISHELL_EXEC)" "$(INSTALL_DIR)/minishell"
	chmod +x "$(INSTALL_DIR)/minishell"
	@echo "✅ Copied minishell to $(INSTALL_DIR)."

	# Add to PATH in .bashrc if not already present
	@if [ -f "$(HOME)/.bashrc" ]; then \
	  if ! grep -q '$(INSTALL_DIR)' "$(HOME)/.bashrc"; then \
	    echo 'export PATH="$(HOME)/.local/bin:$$PATH"' >> "$(HOME)/.bashrc"; \
	    echo "✅ Added PATH to .bashrc"; \
	  fi \
	fi

	# Add to PATH in .zshrc if not already present
	@if [ -f "$(HOME)/.zshrc" ]; then \
	  if ! grep -q '$(INSTALL_DIR)' "$(HOME)/.zshrc"; then \
	    echo 'export PATH="$(HOME)/.local/bin:$$PATH"' >> "$(HOME)/.zshrc"; \
	    echo "✅ Added PATH to .zshrc"; \
	  fi \
	fi

	# Add to PATH in fish config if not already present
	@if [ -f "$(HOME)/.config/fish/config.fish" ]; then \
	  if ! grep -q '$(INSTALL_DIR)' "$(HOME)/.config/fish/config.fish"; then \
	    echo 'set -gx PATH $(HOME)/.local/bin $$PATH' >> "$(HOME)/.config/fish/config.fish"; \
	    echo "✅ Added PATH to fish config"; \
	  fi \
	fi

	@echo "✨ Installation complete! Restart your terminal or run 'source ~/.bashrc' (or equivalent) to apply changes."

lsp-setup:
	@echo "$(TEST_CFLAGS)" | tr ' ' '\n' > compile_flags.txt
	@printf "${GREEN}✔${RESET} compile_flags.txt generated.\n"
set-src-files:
	@echo SRCS = \\ > mk/srcs.mk
	@$(MAKE) get-src-files >> mk/srcs.mk
get-src-files:
	@find ./src -not -type d -name '*.c' ! -name '*_test.c' \
		| sed 's|^\./||' \
		| while read line; do echo $$line \\; done
