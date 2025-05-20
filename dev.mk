# ================================
# 💡 TEST RULES (auto-discovered)
# ================================

# Find all *_test.c files recursively
TEST_SRCS := $(shell find src -name '*_test.c')

# Extract module names (e.g., parser_test.c → parser)
TEST_MODULES := $(patsubst %_test.c,%,$(notdir $(TEST_SRCS)))

# Generate binary names: test_parser, test_lexer, etc.
TEST_BINS := $(addprefix test_,$(TEST_MODULES))

# Default test-all target
test_all: $(TEST_BINS)

# Individual test binary rules
# This compiles: test_parser: parser.c + parser_test.c
test_%:
	@echo "🔧 Compiling $@"
	$(CC) -Wall -Wextra -Werror -Iinclude -o $@ \
		$(shell find src -name "$*.c") \
		$(shell find src -name "$*_test.c")
	@./$@

# Clean all test binaries
clean_tests:
	@echo "🧹 Cleaning test binaries..."
	rm -f test_*
