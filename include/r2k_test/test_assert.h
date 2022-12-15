#ifndef R2K_TEST_ASSERT_H
#define R2K_TEST_ASSERT_H

#include <stdbool.h>
#include <stdio.h>

bool check_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len);
bool check_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len);

#define RUN_EXPECT_EQ(_actual, _expected, value_checker) \
    { \
        char actual_str[100]; \
        char expected_str[100]; \
        g_suite.current_test.successful = value_checker(_actual, _expected, actual_str, expected_str, 100); \
        if (!g_suite.current_test.successful) { \
            printf("%s:%d: Failure\n", __FILE__, __LINE__); \
            printf("Value of: %s\n", #_actual); \
            printf("  Actual: %s\n", actual_str); \
            printf("Expected: %s\n", expected_str); \
        } \
    }

/**
 * Check equality between integral values
 */
#define EXPECT_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, check_int_eq)

/**
 * Check equality between pointer values
 */
#define EXPECT_PTR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, check_ptr_eq)

#endif // R2K_TEST_ASSERT_H
