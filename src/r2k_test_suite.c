#include "r2k_test/r2k_test_suite.h"

#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"
#include "r2k_test/internal/r2k_string_util.h"

typedef enum skip_reason {
    SKIP_REASON_IS_FILTERED,
    SKIP_REASON_IS_DISABLED,
    SKIP_REASON_NONE,
} skip_reason_t;

static skip_reason_t should_skip_test(const char* filter, const char* suite_name, const char* test_name) {
    // only match against filter if it's non-empty
    if (string_empty(filter)) {
        // if not filtered, check if disabled
        if (starts_with(test_name, "DISABLED_")) {
            return SKIP_REASON_IS_DISABLED;
        }
        return SKIP_REASON_NONE;
    }

    char full_test_name[100];
    snprintf(full_test_name, 100, "%s.%s", suite_name, test_name);
    if (!wildcard_prefix_match(filter, full_test_name)) {
        return SKIP_REASON_IS_FILTERED;
    }

    return SKIP_REASON_NONE;
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
        .timer = r2k_timer_start(),
        .current_test = (r2k_test_case_t) {
            .name = NULL,
            .successful = false,
            .skipped = false,
        },
    };
}

void r2k_test_suite_end(r2k_test_suite_t* suite) {
    if (suite->num_ran_tests > 0 && !suite->current_test.skipped) {
        r2k_test_case_end(suite);
    }
    printf_green("[----------] ");
    printf("%d test%s from %s (%d ms total)\n\n",
        suite->num_ran_tests,
        plural_suffix(suite->num_ran_tests),
        suite->name,
        r2k_timer_stop(&suite->timer).value
    );
}

bool r2k_should_skip_suite(const char* suite_name) {
    // if filter doesn't match suite name, it won't match the full test name either
    r2k_test_runner_t* test_runner = r2k_internal_get_test_runner();
    return !(string_empty(test_runner->test_filter) || wildcard_prefix_match(test_runner->test_filter, suite_name));
}

bool r2k_test_case_start(r2k_test_suite_t* suite, const char* test_name) {
    // finish previous test if it wasn't skipped
    if (suite->num_ran_tests > 0 && !suite->current_test.skipped) {
        r2k_test_case_end(suite);
    }

    // reset test case metadata
    suite->current_test.name = test_name;
    suite->current_test.successful = true;
    suite->current_test.skipped = false;

    // check if should skip current test
    switch (should_skip_test(suite->test_runner->test_filter, suite->name, test_name)) {
        case SKIP_REASON_IS_DISABLED:
            printf_yellow("[ DISABLED ] ");
            printf("%s.%s\n", suite->name, suite->current_test.name);
            suite->test_runner->num_disabled_tests += 1;
            suite->current_test.skipped = true;
            return false;
        case SKIP_REASON_IS_FILTERED:
            suite->current_test.skipped = true;
            return false;
        case SKIP_REASON_NONE:
            break;
    }

    // start current test
    suite->timer = r2k_timer_start();
    suite->num_ran_tests += 1;
    suite->test_runner->num_tests += 1;
    printf_green("[ RUN      ] ");
    printf("%s.%s\n", suite->name, suite->current_test.name);

    return true;
}

void r2k_test_case_end(r2k_test_suite_t* suite) {
    if (suite->current_test.successful) {
        suite->test_runner->num_passed_tests += 1;
        printf_green("[       OK ] ");
    } else {
        // add test name to list of failed tests
        char* failed_test_name = suite->test_runner->failed_test_names[suite->test_runner->num_failed_tests];
        snprintf(failed_test_name, R2K_MAX_FAILED_TEST_STR_LEN, "%s.%s", suite->name, suite->current_test.name);

        suite->test_runner->num_failed_tests += 1;
        printf_red("[  FAILED  ] ");
    }
    printf("%s.%s (%d ms)\n",
        suite->name,
        suite->current_test.name,
        r2k_timer_stop(&suite->timer).value
    );
}

