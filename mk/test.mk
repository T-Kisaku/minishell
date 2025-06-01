
# dev.mk — minishell C test harness with obj dir
MKFILE       := mk/test.mk
TEST_BIN_DIR := test_bin
CFLAGS       := -Iinclude -I$(LIBFTDIR) -lreadline -g

# -----------------------------------------------------------------------------
# Test modules
# -----------------------------------------------------------------------------
TEST_MODS := $(patsubst %_test.c,%,$(notdir $(TEST_SRCS)))

TEST_SRCS := $(shell find $(SRC_DIR) -type f -name '*.c' \
               -not -name '*_test.c' -not -name 'minishell.c')
TEST_OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))

.PHONY: test_all test_fclean %_test

test_all:
	$(MAKE) -f $(MKFILE) $(addsuffix _test,$(TEST_MODS))

# -----------------------------------------------------------------------------
# Build & run a single test (supports both src/mod/mod_test.c and src/mod_test.c)
# -----------------------------------------------------------------------------
%_test:
	@$(MAKE) $(LIBFT)
	@$(MAKE) $(TEST_OBJS) CFLAGS="$(CFLAGS)"
	@mkdir -p $(TEST_BIN_DIR)
	$(eval TEST_SRC := $(firstword $(wildcard \
	  $(SRC_DIR)/$*/$*_test.c \
	  $(SRC_DIR)/$*_test.c)))
	@$(MAKE) print_compiling TARGET="$(TEST_SRC)"
	$(CC) $(CFLAGS) $(TEST_SRC) $(TEST_OBJS) $(LIBFT) -o $(TEST_BIN_DIR)/$*_test
	@$(MAKE) print_running TARGET="$(TEST_BIN_DIR)/$*_test"
	@valgrind --leak-check=full --quiet ./$(TEST_BIN_DIR)/$*_test

# -----------------------------------------------------------------------------
# Cleanup
# -----------------------------------------------------------------------------
test_fclean:
	rm -rf $(TEST_BIN_DIR)
	@$(MAKE) print_finished MSG="Removed test bins!"
