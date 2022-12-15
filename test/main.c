#include <stddef.h>
#include <stdio.h>

// TODO:
// [x] Print start and end of test suite
// [ ] 1 suite with 1 case
// [ ] 1 passing test
// [ ] 1 failing test with EXPECT_EQ
// [ ] print args to EXPECT_EQ on failure

#include "r2k_test/internal/windows.h"
#include "r2k_test/internal/color_print.h"

typedef struct test_runner {
    size_t num_tests;
    size_t num_suites;
    size_t num_milliseconds;
} test_runner_t;

void init_terminal(void) {
#ifdef WIN32
    enable_windows_virtual_terminal();
#endif // WIN32
}

test_runner_t test_start(void) {
    init_terminal();

    printf_green("[==========] ");
    printf("Running tests.\n");

    printf_green("[----------] ");
    printf("Global test environment set-up.\n");

    return (test_runner_t) {
        .num_tests = 0,
        .num_suites = 0,
        .num_milliseconds = 0,
    };
}

void test_end(const test_runner_t* runner) {
    printf("\n");

    printf_green("[----------] ");
    printf("Global test environment tear-down\n");

    printf_green("[==========] ");
    printf("%d tests from %d test suites ran. (%d ms total)\n",
        runner->num_tests,
        runner->num_suites,
        runner->num_milliseconds
    );
}

int main(void) {
    test_runner_t runner = test_start();
    test_end(&runner);
    return 0;
}
