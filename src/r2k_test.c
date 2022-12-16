#include "r2k_test/r2k_test.h"

#include "r2k_test/internal/windows.h"
#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"
#include "r2k_test/internal/r2k_string_util.h"

static void init_terminal(void) {
#ifdef WIN32
    enable_windows_virtual_terminal();
#endif // WIN32
}

static void parse_args(int argc, char** argv) {
    if (argc > 0) {
        const char* test_filter_prefix = "--test_filter=";
        if (starts_with(argv[1], test_filter_prefix)) {
            const char* arg_value = argv[1] + strlen(test_filter_prefix);
            r2k_test_runner_t* test_runner = r2k_internal_get_test_runner();
            strncpy(test_runner->test_filter, arg_value, 100);
            printf_yellow("Note: Test filter = %s\n", test_runner->test_filter);
        }
    }
}

void r2k_test_start(int argc, char** argv) {
    init_terminal();
    parse_args(argc, argv);

    printf_green("[==========] ");
    printf("Running tests.\n");

    printf_green("[----------] ");
    printf("Global test environment set-up.\n");
}

r2k_test_result_t r2k_test_end() {
    const r2k_test_runner_t* test_runner = r2k_internal_get_test_runner();

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

    const size_t num_failed_tests = test_runner->num_failed_tests;
    if (num_failed_tests > 0) {
        printf_red("[  FAILED  ] ");
        printf("%d test%s, listed below:\n", num_failed_tests, plural_suffix(num_failed_tests));
        for (size_t i = 0; i < num_failed_tests; i++) {
            printf_red("[  FAILED  ] ");
            printf("%s\n", test_runner->failed_test_names[i]);
        }

        return R2K_TEST_FAILED;
    }

    return R2K_TEST_OK;
}
