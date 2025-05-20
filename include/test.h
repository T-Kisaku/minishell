#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define ASSERT_EQ_INT(expected, actual) \
	if ((expected) != (actual)) \
		printf("❌ %s:%d: expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
	else \
		printf("✅ %s:%d: passed\n", __FILE__, __LINE__);

#define ASSERT_TRUE(cond) \
	if (!(cond)) \
		printf("❌ %s:%d: condition failed\n", __FILE__, __LINE__); \
	else \
		printf("✅ %s:%d: passed\n", __FILE__, __LINE__);

#endif
