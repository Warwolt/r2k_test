#include "r2k_test/r2k_test.h"
#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TEST_SUITE_START(runner) \
    test_suite_t g_suite = (test_suite_t) { \
        .test_runner = runner, \
        .name = __func__, \
        .num_ran_tests = 0, \
        .current_test = { \
            .suite = __func__, \
            .name = NULL, \
            .successful = false, \
        }, \
    }; \
    g_suite.test_runner->num_suites += 1

#define TEST_SUITE_END(runner) \
    print_case_result(&g_suite.current_test); \
    printf_green("[----------] "); \
    printf("%d test%s from %s (0 ms total)\n\n", \
        g_suite.num_ran_tests, \
        plural_suffix(g_suite.num_ran_tests), \
        g_suite.name \
    )

typedef struct test_case {
    const char* suite;
    const char* name;
    bool successful;
} test_case_t;

typedef struct test_suite {
    r2k_test_runner_t* test_runner;
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

void start_test_case(test_suite_t* suite, const char* case_name) {
    if (suite->num_ran_tests > 0) {
        print_case_result(&suite->current_test);
    }

    suite->num_ran_tests += 1;
    suite->current_test.name = case_name;
    suite->current_test.successful = true;

    printf_green("[ RUN      ] ");
    printf("%s.%s\n", suite->name, suite->current_test.name);
    suite->test_runner->num_tests += 1;
}

void dummy_tests(r2k_test_runner_t* runner) {
    TEST_SUITE_START(runner);

    printf_green("[----------] ");
    printf("Running tests from %s\n", __func__);

    start_test_case(&g_suite, "integers");
    EXPECT_EQ(2 + 2, 5);

    start_test_case(&g_suite, "chars");
    EXPECT_CHAR_EQ('A', 'a');

    start_test_case(&g_suite, "pointers");
    int a, b;
    EXPECT_PTR_EQ(&a, &b);

    start_test_case(&g_suite, "strings");
    EXPECT_STR_EQ("foo", "bar");

    start_test_case(&g_suite, "float");
    EXPECT_FLOAT_NEAR(1.0f, 2.0f, 0.01);

    start_test_case(&g_suite, "double");
    EXPECT_DOUBLE_NEAR(1.0, 2.01, 0.01);

    TEST_SUITE_END(runner);
}

int main(void) {
    r2k_test_runner_t runner = r2k_test_start();

    dummy_tests(&runner);

    r2k_test_end(&runner);
    return 0;
}
