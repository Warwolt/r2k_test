#include "r2k_test/r2k_test.h"

#include "r2k_test/internal/windows.h"
#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"

static void init_terminal(void) {
#ifdef WIN32
    enable_windows_virtual_terminal();
#endif // WIN32
}

void r2k_test_start(void) {
    init_terminal();

    printf_green("[==========] ");
    printf("Running tests.\n");

    printf_green("[----------] ");
    printf("Global test environment set-up.\n");
    _r2k_internal_init_test_runner();
}

void r2k_test_end() {
    const r2k_test_runner_t* test_runner = _r2k_internal_get_test_runner();

    printf_green("[----------] ");
    printf("Global test environment tear-down\n");

    printf_green("[==========] ");
    printf("%d test%s from %d test suite%s ran. (%d ms total)\n",
        test_runner->num_tests,
        plural_suffix(test_runner->num_tests),
        test_runner->num_suites,
        plural_suffix(test_runner->num_suites),
        test_runner->total_milliseconds
    );

    printf_green("[  PASSED  ] ");
    printf("%d test%s.\n", test_runner->num_passed, plural_suffix(test_runner->num_passed));

    const size_t num_failed = test_runner->num_failed;
    if (num_failed > 0) {
        printf_red("[  FAILED  ] ");
        printf("%d test%s, listed below:\n", num_failed, plural_suffix(num_failed));
        printf("TODO add names of failed tests\n");
    }
}

void r2k_test_case_start(test_suite_t* suite, const char* case_name) {
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

void r2k_test_case_end(test_suite_t* suite) {
    if (suite->current_test.successful) {
        suite->test_runner->num_passed += 1;
        printf_green("[       OK ] ");
    } else {
        suite->test_runner->num_failed += 1;
        printf_red("[  FAILED  ] ");
    }
    printf("%s.%s (0 ms)\n", suite->name, suite->current_test.name);
}
