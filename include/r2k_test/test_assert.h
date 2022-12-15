#ifndef R2K_TEST_ASSERT_H
#define R2K_TEST_ASSERT_H

#include <stdbool.h>
#include <stdio.h>

bool expect_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len);
bool expect_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len);

#define CHECK_INT_OR_PTR_EQ(actual, expected, actual_str, expected_str, buf_len) _Generic((actual), \
      int: expect_int_eq((int)(actual), (int)(expected), actual_str, expected_str, buf_len), \
      default: expect_ptr_eq((void *)(actual), (void *)(expected), actual_str, expected_str, buf_len))

#define RUN_EXPECT_EQ(_actual, _expected, checker_macro) \
    { \
        char actual_str[100]; \
        char expected_str[100]; \
        g_suite.current_test.successful = checker_macro(_actual, _expected, actual_str, expected_str, 100); \
        if (!g_suite.current_test.successful) { \
            printf("%s:%d: Failure\n", __FILE__, __LINE__); \
            printf("Value of: %s\n", #_actual); \
            printf("  Actual: %s\n", actual_str); \
            printf("Expected: %s\n", expected_str); \
        } \
    }

/**
 * Check equality between integral or pointer values
 *
 * Must be between a TEST_START() and TEST_END() pair.
 *
 * @param actual the computed value
 * @param actual the value to check against
 */
#define EXPECT_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, CHECK_INT_OR_PTR_EQ)

#endif // R2K_TEST_ASSERT_H
