# dev.mk — minishell C test harness with obj dir
TEST_BIN_DIR 			:= test_bin
TEST_CFLAGS				:= $(INCLUDE_FLAGS) -Itestdata -g

TEST_SRCS := $(filter-out src/minishell.c,$(SRCS))
TEST_OBJS := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(TEST_SRCS:.c=.o))
TEST_MODS := $(basename $(notdir $(shell find src -name '*_test.c')))

PHONY_TARGETS += test_all test_fclean %_test

test: test_all
test_all:
	$(MAKE) $(TEST_MODS)

%_test: | $(TEST_BIN_DIR)
	@$(MAKE) $(LIBFT)
	@$(MAKE) $(TEST_OBJS) CFLAGS="$(TEST_CFLAGS)"
	@$(MAKE) $(TESTDATA_OBJS) CFLAGS="$(TEST_CFLAGS)"
	$(eval TEST_SRC := $(shell find src -type f -name "$*_test.c" | head -n 1))
	@$(MAKE) print_compiling TARGET="$(TEST_SRC)"
	$(CC) $(TEST_CFLAGS) $(TEST_SRC) $(TEST_OBJS) $(TESTDATA_OBJS) $(LIBFT) -o $(TEST_BIN_DIR)/$*_test
	@$(MAKE) print_running TARGET="$(TEST_BIN_DIR)/$*_test"
	@valgrind --leak-check=full --quiet ./$(TEST_BIN_DIR)/$*_test

$(TEST_BIN_DIR):
	@$(MKDIR_P) $@

test_clean: clean testdata_clean

test_fclean: test_clean
	rm -rf $(TEST_BIN_DIR)
	@$(MAKE) print_finished MSG="Removed test bins!"

test_re: test_fclean test_all
