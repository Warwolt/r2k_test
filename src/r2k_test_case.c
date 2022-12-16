#include "r2k_test/r2k_test_case.h"

#include "r2k_test/internal/r2k_color_print.h"

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
        suite->test_runner->num_failed += 1;
        printf_red("[  FAILED  ] ");
    }
    printf("%s.%s (0 ms)\n", suite->name, suite->current_test.name);
}
