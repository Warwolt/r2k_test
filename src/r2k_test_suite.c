#include "r2k_test/r2k_test_suite.h"

#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"

#include <string.h>

// returns true if either lhs == rhs or matches up until asterix
bool wild_card_match(const char* lhs, const char* rhs) {
    while (*lhs && *rhs) {
        if (*lhs == '*') {
            return true; // prefix matches
        }
        if (*lhs != *rhs) {
            return false; // not matching
        }
        lhs++;
        rhs++;
    }
    return true;
}

static bool should_skip_test(const char* filter, const char* full_test_name) {
    // check if filter empty
    if (*filter == '\0') {
        return false;
    }

    return !wild_card_match(filter, full_test_name);
}

r2k_test_suite_t r2k_test_suite_start(const char* suite_name) {
    r2k_test_runner_t* test_runner = r2k_internal_get_test_runner();
    test_runner->num_suites += 1;

    printf_green("[----------] ");
    printf("Running tests from %s\n", suite_name);

    return (r2k_test_suite_t) {
        .test_runner = test_runner,
        .name = suite_name,
        .num_ran_tests = 0,
        .current_test = (r2k_test_case_t) {
            .name = NULL,
            .successful = false,
            .skipped = false,
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

bool r2k_test_case_start(r2k_test_suite_t* suite, const char* test_name) {
    // finish previous test if it wasn't skipped
    if (suite->num_ran_tests > 0 && !suite->current_test.skipped) {
        r2k_test_case_end(suite);
    }
    suite->current_test.successful = true;
    suite->current_test.skipped = false;
    suite->current_test.name = test_name;

    // check if should skip current test
    char full_test_name[100];
    snprintf(full_test_name, 100, "%s.%s", suite->name, test_name);
    if (should_skip_test(suite->test_runner->test_filter, full_test_name)) {
        suite->current_test.skipped = true;
        return false;
    }

    // start current test
    suite->num_ran_tests += 1;
    suite->test_runner->num_tests += 1;

    printf_green("[ RUN      ] ");
    printf("%s.%s\n", suite->name, suite->current_test.name);

    return true;
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

