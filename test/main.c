#include "r2k_test/r2k_test.h"
#include "r2k_test/internal/color_print.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool expect_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "%d", actual);
        snprintf(expected_str, buf_len, "%d", expected);
        return false;
    }
    return true;
}

bool expect_ptr_eq(const void* actual, const void* expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "0x%p", actual);
        snprintf(expected_str, buf_len, "0x%p", expected);
        return false;
    }
    return true;
}

#define EXPECT_INT_OR_PTR_EQ(actual, expected, actual_str, expected_str, buf_len) _Generic((actual), \
      int: expect_int_eq((int)(actual), (int)(expected), actual_str, expected_str, buf_len), \
      default: expect_ptr_eq((void *)(actual), (void *)(expected), actual_str, expected_str, buf_len))

// used for checking equality between integral or pointer types
#define EXPECT_EQ(_actual, _expected) \
    { \
        char actual_str[100]; \
        char expected_str[100]; \
        suite.current_test.successful = EXPECT_INT_OR_PTR_EQ(_actual, _expected, actual_str, expected_str, 100); \
        if (!suite.current_test.successful) { \
            printf("%s:%d: Failure\n", __FILE__, __LINE__); \
            printf("Value of: %s\n", #_actual); \
            printf("  Actual: %s\n", actual_str); \
            printf("Expected: %s\n", expected_str); \
        } \
    }

typedef struct test_case {
    const char* suite;
    const char* name;
    bool successful;
} test_case_t;

typedef struct test_suite {
    const char* name;
    size_t num_ran_tests;
    test_case_t current_test;
} test_suite_t;

void print_case_result(const test_case_t* test) {
    if (test->successful) {
        printf_green("[       OK ] ");
    } else {
        printf_red("[  FAILED  ] ");
    }
    printf("%s.%s (0 ms)\n", test->suite, test->name);
}

void start_test_case(r2k_test_runner_t* runner, test_suite_t* suite, const char* case_name) {
    if (suite->num_ran_tests > 0) {
        print_case_result(&suite->current_test);
    }

    suite->num_ran_tests += 1;
    suite->current_test.name = case_name;
    suite->current_test.successful = true;

    printf_green("[ RUN      ] ");
    printf("%s.%s\n", suite->name, suite->current_test.name);
    runner->num_tests += 1;
}

void dummy_tests(r2k_test_runner_t* runner) {
    runner->num_suites += 1;
    test_suite_t suite = (test_suite_t) {
        .name = __func__,
        .num_ran_tests = 0,
        .current_test = {
            .suite = __func__,
            .name = NULL,
            .successful = false,
        },
    };

    printf_green("[----------] ");
    printf("Running tests from %s\n", __func__);

    start_test_case(runner, &suite, "hello");
    EXPECT_EQ(2 + 2, 5);

    start_test_case(runner, &suite, "world");

    print_case_result(&suite.current_test);

    printf_green("[----------] ");
    printf("1 test from %s (0 ms total)\n\n", __func__);
}

int main(void) {
    r2k_test_runner_t runner = r2k_test_start();

    dummy_tests(&runner);

    r2k_test_end(&runner);
    return 0;
}
