PHONY_TARGETS += norm lsp-setup get-src-files format stdheader
norm:
	@norminette include | grep -v "OK!" || true
	@norminette $(SRC_DIR) | grep -v "OK!" || true
	@$(MAKE) norm -C $(LIBFTDIR)

lsp-setup:
	@echo "-Iinclude" > compile_flags.txt
	@echo "-I$(LIBFTDIR)" >> compile_flags.txt
	@printf "${GREEN}✔${RESET} compile_flags.txt generated.\n"

get-src-files:
	@find ./src -not -type d -name '*.c' ! -name '*_test.c' \
		| sed 's|^\./||' \
		| sed '$$!s|$$| \\\\|' \
		| while read line; do echo $$line; done
format:
	@c_formatter_42 $(wildcard include/*.h) $(wildcard include/**/*.h)
	@c_formatter_42 $(SRCS)
	@$(MAKE) format -C $(LIBFTDIR)

stdheader:
	@stdheader $(wildcard include/*.h) $(wildcard include/**/*.h)
	@stdheader $(SRCS)
