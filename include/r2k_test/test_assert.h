#ifndef R2K_TEST_ASSERT_H
#define R2K_TEST_ASSERT_H

#include <stdbool.h>
#include <stdio.h>

bool r2k_check_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_char_eq(char actual, char expected, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_str_eq(const char* actual, const char* expected, char* actual_str, char* expected_str, int buf_len);

bool r2k_check_float_near(float actual, float expected, float abs_error, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_double_near(double actual, double expected, float abs_error, char* actual_str, char* expected_str, int buf_len);

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

#define RUN_EXPECT_NEAR(_actual, _expected, abs_error, value_checker) \
    { \
        char actual_str[100]; \
        char expected_str[100]; \
        g_suite.current_test.successful = value_checker(_actual, _expected, abs_error, actual_str, expected_str, 100); \
        if (!g_suite.current_test.successful) { \
            printf("%s:%d: Failure\n", __FILE__, __LINE__); \
            printf("Value of: %s\n", #_actual); \
            printf("  Actual: %s\n", actual_str); \
            printf("Expected: %s\n", expected_str); \
            printf("note: tolerance is %d\n", abs_error); \
        } \
    }

#define EXPECT_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_int_eq)
#define EXPECT_CHAR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_char_eq)
#define EXPECT_PTR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_ptr_eq)
#define EXPECT_STR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_str_eq)

#define EXPECT_FLOAT_NEAR(actual, expected, abs_error) RUN_EXPECT_NEAR(actual, expected, abs_error, r2k_check_float_near)
#define EXPECT_DOUBLE_NEAR(actual, expected, abs_error) RUN_EXPECT_NEAR(actual, expected, abs_error, r2k_check_double_near)

#endif // R2K_TEST_ASSERT_H
