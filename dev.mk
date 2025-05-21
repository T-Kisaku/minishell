
CC       ?= cc
CFLAGS   = -Wall -Wextra -Werror -Iinclude

TEST_SRCS    := $(shell find src -type f -name '*_test.c')
TEST_MODULES := $(patsubst %_test.c,%,$(notdir $(TEST_SRCS)))
TEST_BINS    := $(addprefix test_,$(TEST_MODULES))

.PHONY: test_all clean_tests

test_all: $(TEST_BINS)
	@echo "🔧 Running all tests…"
	@for t in $(TEST_BINS); do               \
	  echo "→ $$t";                         \
	  ./$$t || exit 1;                     \
	done

$(TEST_BINS): test_%:
	@echo "🔧 Compiling $@"
	@$(CC) $(CFLAGS) -o $@                                   \
	  $(shell find src -type f -name "$*.c")                \
	  $(shell find src -type f -name "$*_test.c")

clean_tests:
	@echo "🧹 Cleaning test binaries..."
	@rm -f $(TEST_BINS)

test_re: clean_tests test_all

