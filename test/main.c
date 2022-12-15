#include "r2k_test/r2k_test.h"
#include "r2k_test/internal/color_print.h"

#include <stdio.h>
#include <stdbool.h>

#define EXPECT_EQ(actual, expected) \
    if (actual != expected) { \
        suite.current_test.successful = false; \
        printf("%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("Value of: %s\n", #actual); \
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
