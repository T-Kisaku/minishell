
#include "../include/minishell.h"  // or your own header
#include "../include/test.h"         // path depends on your structure

int dummy_add(int a, int b) {
	return a + b;
}

int main(void) {
	ASSERT_EQ_INT(3, dummy_add(1, 2));
	ASSERT_EQ_INT(5, dummy_add(2, 2)); // this will fail
	ASSERT_TRUE(1 == 1);
	ASSERT_TRUE(0); // this will fail
	return 0;
}
