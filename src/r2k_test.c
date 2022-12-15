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
        test_runner->num_milliseconds
    );
}
