#include "r2k_test/r2k_test.h"
#include "r2k_test/internal/color_print.h"

#include <stdio.h>
#include <stdbool.h>

typedef struct test_case {
    const char* suite;
    const char* name;
    bool successful;
} test_case_t;

typedef struct test_suite {
    test_case_t current_test;
    size_t num_ran_tests;
} test_suite_t;

void print_case_result(const test_case_t* test) {
    printf_green("[       OK ] ");
    printf("%s.%s (0 ms)\n", test->suite, test->name);
}

void dummy_tests(r2k_test_runner_t* runner) {
    runner->num_suites += 1;
    test_suite_t suite = (test_suite_t) {
        .current_test = {
            .suite = __func__,
            .name = NULL,
            .successful = false,
        },
        .num_ran_tests = 0,
    };

    printf_green("[----------] ");
    printf("Running tests from %s\n", __func__);

    {
        if (suite.num_ran_tests > 0) {
            print_case_result(&suite.current_test);
        }

        suite.num_ran_tests += 1;
        suite.current_test.name = "hello";

        printf_green("[ RUN      ] ");
        printf("%s.%s\n", __func__, suite.current_test.name);
        runner->num_tests += 1;
    }

    {
        if (suite.num_ran_tests > 0) {
            print_case_result(&suite.current_test);
        }

        suite.num_ran_tests += 1;
        suite.current_test.name = "world";

        printf_green("[ RUN      ] ");
        printf("%s.%s\n", __func__, suite.current_test.name);
        runner->num_tests += 1;
    }

    print_case_result(&suite.current_test);

    printf_green("[----------] ");
    printf("1 test from %s (0 ms total)\n\n", __func__);

    runner->num_tests += suite.num_ran_tests;
}

int main(void) {
    r2k_test_runner_t runner = r2k_test_start();

    dummy_tests(&runner);

    r2k_test_end(&runner);
    return 0;
}
