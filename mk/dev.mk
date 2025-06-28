PHONY_TARGETS += norm lsp-setup get-src-files format stdheader
norm:
	@norminette $(SRC_DIR) | grep -v "OK!" || true
	@$(MAKE) norm -C $(LIBFTDIR)

lsp-setup:
	@echo "$(TEST_CFLAGS)" | tr ' ' '\n' > compile_flags.txt
	@printf "${GREEN}✔${RESET} compile_flags.txt generated.\n"

format:
	@c_formatter_42 $(wildcard include/*.h) $(wildcard include/**/*.h)
	@c_formatter_42 $(SRCS)
	@$(MAKE) format -C $(LIBFTDIR)

stdheader:
	@stdheader $(wildcard include/*.h) $(wildcard include/**/*.h)
	@stdheader $(SRCS)

set-src-files:
	@echo SRCS = \\ > mk/srcs.mk
	@$(MAKE) get-src-files >> mk/srcs.mk
get-src-files:
	@find ./src -not -type d -name '*.c' ! -name '*_test.c' \
		| sed 's|^\./||' \
		| while read line; do echo $$line \\; done

INSTALL_DIR := $(HOME)/.local/bin
MINISHELL_EXEC := minishell


dev:
	@$(MAKE) set-src-files
	@$(MAKE) install
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp minishell

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
