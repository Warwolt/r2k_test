#include "r2k_test/r2k_test_suite.h"

#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"


r2k_test_suite_t r2k_test_suite_start(const char* suite_name) {
    r2k_test_runner_t* test_runner = r2k_internal_get_test_runner();
    test_runner->num_suites += 1;

    printf_green("[----------] ");
    printf("Running tests from %s\n", suite_name);

    return (r2k_test_suite_t) {
        .test_runner = test_runner,
        .name = suite_name,
        .num_ran_tests = 0,
        .current_test = {
            .name = NULL,
            .successful = false,
        },
    };
}

void r2k_test_suite_end(r2k_test_suite_t* suite) {
    if (suite->num_ran_tests > 0) {
        r2k_test_case_end(suite);
    }
    printf_green("[----------] ");
    printf("%d test%s from %s (0 ms total)\n\n",
        suite->num_ran_tests,
        plural_suffix(suite->num_ran_tests),
        suite->name
    );
}

void r2k_test_case_start(r2k_test_suite_t* suite, const char* case_name) {
    // finish previous test case
    if (suite->num_ran_tests > 0) {
        r2k_test_case_end(suite);
    }

    // start current test case
    suite->num_ran_tests += 1;
    suite->current_test.name = case_name;
    suite->current_test.successful = true;
    suite->test_runner->num_tests += 1;

    printf_green("[ RUN      ] ");
    printf("%s.%s\n", suite->name, suite->current_test.name);
}

void r2k_test_case_end(r2k_test_suite_t* suite) {
    if (suite->current_test.successful) {
        suite->test_runner->num_passed += 1;
        printf_green("[       OK ] ");
    } else {
        // add test name to list of failed tests
        char* failed_test_name = suite->test_runner->failed_test_names[suite->test_runner->num_failed_tests];
        snprintf(failed_test_name, R2K_MAX_FAILED_TEST_STR_LEN, "%s.%s", suite->name, suite->current_test.name);

        suite->test_runner->num_failed_tests += 1;
        printf_red("[  FAILED  ] ");
    }
    printf("%s.%s (0 ms)\n", suite->name, suite->current_test.name);
}
