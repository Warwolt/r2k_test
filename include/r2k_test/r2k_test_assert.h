#ifndef R2K_TEST_ASSERT_H
#define R2K_TEST_ASSERT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "r2k_test/r2k_test_suite.h"

bool r2k_check_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_char_eq(char actual, char expected, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_str_eq(const char* actual, const char* expected, char* actual_str, char* expected_str, int buf_len);

bool r2k_check_float_near(float actual, float expected, float abs_error, char* diff_str, char* actual_str, char* expected_str, int buf_len);
bool r2k_check_double_near(double actual, double expected, float abs_error, char* diff_str, char* actual_str, char* expected_str, int buf_len);

#define RUN_EXPECT_BOOL(actual, bool_val) \
    { \
        bool actual_val = actual; \
        _R2K_TEST_SUITE.current_test.successful = (actual_val == bool_val); \
        if (!_R2K_TEST_SUITE.current_test.successful) { \
            printf(" error: Value of: %s\n", #actual); \
            printf("  Actual: %s\n", actual_val ? "true" : "false"); \
            printf("Expected: %s\n", bool_val ? "true" : "false"); \
        } \
    }

#define RUN_EXPECT_EQ(_actual, _expected, value_checker) \
    { \
        char actual_str[100]; \
        char expected_str[100]; \
        _R2K_TEST_SUITE.current_test.successful = value_checker(_actual, _expected, actual_str, expected_str, 100); \
        if (!_R2K_TEST_SUITE.current_test.successful) { \
            printf("%s(%d): error: Expected equality of these values:\n", __FILE__, __LINE__); \
            printf("  %s\n", #_actual); \
            printf("    Which is: %s\n", actual_str); \
            printf("  %s\n", expected_str); \
        } \
    }

#define RUN_EXPECT_NEAR(_actual, _expected, abs_error, value_checker) \
    { \
        char diff_str[100]; \
        char actual_str[100]; \
        char expected_str[100]; \
        _R2K_TEST_SUITE.current_test.successful = value_checker(_actual, _expected, abs_error, diff_str, actual_str, expected_str, 100); \
        if (!_R2K_TEST_SUITE.current_test.successful) { \
            printf("%s:%d: Failure\n", __FILE__, __LINE__); \
            printf("%s(%d): error: The difference between %s and %s is %s, which exceeds %s, where\n", \
                __FILE__, \
                __LINE__, \
                #_actual, \
                #_expected, \
                diff_str, \
                #abs_error \
            ); \
            printf("%s evaluates to %s\n", #_actual, actual_str); \
            printf("%s evaluates to %s, and\n", #_expected, expected_str); \
            printf("%s evaluates to %f\n", #abs_error, abs_error); \
        } \
    }

#define EXPECT_TRUE(actual) RUN_EXPECT_BOOL(actual, true)
#define EXPECT_FALSE(actual) RUN_EXPECT_BOOL(actual, false)

#define EXPECT_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_int_eq)
#define EXPECT_CHAR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_char_eq)
#define EXPECT_PTR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_ptr_eq)
#define EXPECT_STR_EQ(actual, expected) RUN_EXPECT_EQ(actual, expected, r2k_check_str_eq)

#define EXPECT_FLOAT_NEAR(actual, expected, abs_error) RUN_EXPECT_NEAR(actual, expected, abs_error, r2k_check_float_near)
#define EXPECT_DOUBLE_NEAR(actual, expected, abs_error) RUN_EXPECT_NEAR(actual, expected, abs_error, r2k_check_double_near)

#endif // R2K_TEST_ASSERT_H
