TESTDATA_DIR  := testdata
TESTDATA_OBJ_DIR  := $(TESTDATA_DIR)/$(OBJ_DIR)
TESTDATA_SRCS := $(wildcard $(TESTDATA_DIR)/*.c)
TESTDATA_OBJS := $(patsubst $(TESTDATA_DIR)/%.c,$(TESTDATA_OBJ_DIR)/%.o,$(TESTDATA_SRCS))

PHONY_TARGETS += testdata testdata_all testdata_clean testdata_re

testdata: testdata_all
testdata_all: $(TESTDATA_OBJS)

$(TESTDATA_OBJ_DIR)/%.o: $(TESTDATA_DIR)/%.c | $(TESTDATA_OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(MAKE) print_compiling TARGET="${notdir $<}"

$(TESTDATA_OBJ_DIR):
	@$(MKDIR_P) $@
	
testdata_clean:
	@$(RM) -rf $(TESTDATA_OBJ_DIR)
	@$(MAKE) print_finished MSG="Test data objects cleaned"

testdata_re: testdata_clean testdata_all

.PHONY: 
