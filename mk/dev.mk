include mk/config.mk
norm:
	@norminette include | grep -v "OK!" || true
	@norminette $(SRC_DIR) | grep -v "OK!" || true
	@$(MAKE) norm -C $(LIBFTDIR)

lsp-setup:
	@echo "-Iinclude" > compile_flags.txt
	@echo "-I$(LIBFTDIR)" >> compile_flags.txt
	@printf "${GREEN}✔${RESET} compile_flags.txt generated.\n"


# TODO: updat get source files func
SRC_FILES := $(shell find $(SRC_DIR) -type f -name '*.c' \
               -not -name '*_test.c' -not -name 'main.c')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
get-src-files:
	@find ./src -not -type d -name '*.c' | sed 's|^\./||' | sed '$$!s|$$| \\\\|' | while read line; do echo $$line; done
format:
	@c_formatter_42 $(wildcard include/*.h) $(wildcard include/**/*.h)
	@c_formatter_42 $(SRCS)
	@$(MAKE) format -C $(LIBFTDIR)

stdheader:
	@stdheader $(wildcard include/*.h) $(wildcard include/**/*.h)
	@stdheader $(SRCS)


GDB_FILE = init.gdb
GDB_DATA = H4sICHQPD2gAA2luaXQuZ2RiAG1S7W6DIBT971OcNO2vrabue8u6F+kag3J1pBSdYJbt6XcLUbGtieLlfHDgIqlShtB2yrjcOlEeEsCSw1Jhiw0XP19K06l8hxROpJ6UWvVHDAKq8tStB9cfAa1UZ10ucuUpCPYVFkABj32axQW0Ds81SMxVZGQyJ+xWcs95V5IptxzodhaHNB3JOLtbqr0Xjhvkzw2yJFieXqGVsGgtY/GZJDI+p6alTjjVGJtMIUrRilK53zesdO9jhAgTOR0okcrSd0+mJFbZ66KBEcdr2jFflGUe8mQ0LDR29kITmcrR00sHN93Us4vBda1MzR3haxHOt5ZFytNnhMbwRNWJI12PwbsPDZ2Jqspnulg9F1ozt8htq5Xjv643eTZd0Mw3Ng4LlI1xyvQU9XfwZbUX84h7POIFr3jABk94Roa7GXdas+hIHOCrXJzVRdD8AxKDUfZRAwAA
gdb: gdb-setup
	@make re CFLAGS="$(DFLAGS)" > /dev/null
	gdb -x "$(GDB_FILE)"  -tui ./$(NAME)

gdb-compress:
	@gzip -c "$(GDB_FILE)" | base64 -w 0

gdb-setup:
	@if [ ! -f "$(GDB_FILE)" ]; then \
		echo "$(GDB_DATA)" | base64 -d | gunzip > "$(GDB_FILE)"; \
	else \
		echo "$(GDB_FILE) already exists."; \
	fi

