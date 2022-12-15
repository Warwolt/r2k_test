#include "r2k_test/r2k_test.h"

#include "r2k_test/internal/windows.h"
#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"

static void init_terminal(void) {
#ifdef WIN32
    enable_windows_virtual_terminal();
#endif // WIN32
}

r2k_test_runner_t r2k_test_start(void) {
    init_terminal();

    printf_green("[==========] ");
    printf("Running tests.\n");

    printf_green("[----------] ");
    printf("Global test environment set-up.\n");

    return (r2k_test_runner_t) {
        .num_tests = 0,
        .num_suites = 0,
        .num_milliseconds = 0,
    };
}

void r2k_test_end(const r2k_test_runner_t* runner) {
    printf_green("[----------] ");
    printf("Global test environment tear-down\n");

    printf_green("[==========] ");
    printf("%d test%s from %d test suite%s ran. (%d ms total)\n",
        runner->num_tests,
        plural_suffix(runner->num_tests),
        runner->num_suites,
        plural_suffix(runner->num_suites),
        runner->num_milliseconds
    );
}
