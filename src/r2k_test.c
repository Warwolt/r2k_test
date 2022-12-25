#include <r2k_test/r2k_test.h>

#include <r2k_test/internal/r2k_cli_flags.h>
#include <r2k_test/internal/r2k_color_print.h>
#include <r2k_test/internal/r2k_print_util.h>
#include <r2k_test/internal/r2k_string_util.h>
#include <r2k_test/internal/r2k_arraylen.h>
#ifdef WIN32
#include <r2k_test/internal/r2k_windows.h>
#include <windows.h>
#endif // WIN32

#include <math.h>
#include <stdlib.h>
#include <string.h>

static void init_terminal(void) {
#ifdef WIN32
    enable_windows_virtual_terminal();
#endif // WIN32
}

// --test_filter=<pattern>
static void parse_test_filter(r2k_test_runner_t* test_runner, const char* arg) {
    strncpy(test_runner->test_filter, arg + strlen(TEST_FILTER_FLAG) + 1, R2K_MAX_TEST_FILTER_LEN);
}

#ifdef WIN32
static void parse_death_test_win32(r2k_test_runner_t* test_runner, const char* arg) {
    const char* arg_val = arg + strlen(DEATH_TEST_FLAG) + 1;

    str_slice_t line_num_slice = get_brace_list_value(arg_val, 0);
    char line_num_str[16] = {0};
    strncpy(line_num_str, line_num_slice.str, fmin(line_num_slice.len, arraylen(line_num_str)));
    test_runner->death_test.line_num = atoi(line_num_str);
    printf("line_num = %d\n", test_runner->death_test.line_num);

    str_slice_t pipe_handle_slice = get_brace_list_value(arg_val, 1);
    char pipe_handle_str[32] = {0};
    strncpy(pipe_handle_str, pipe_handle_slice.str, fmin(pipe_handle_slice.len, arraylen(line_num_str)));
    sscanf(pipe_handle_str, "%lu", (unsigned long*)&test_runner->death_test.pipe_handle);

}
#endif

// --r2k-test-internal-run-death-test=<line_number>,<pipe_handle>
static void parse_death_test(r2k_test_runner_t* test_runner, const char* arg) {
    test_runner->death_test.has_been_started = true;
#ifdef WIN32
    parse_death_test_win32(test_runner, arg);
#endif
}

static void parse_args(r2k_test_runner_t* test_runner, int argc, char** argv) {
    test_runner->death_test.executable_path = argv[0];
    for (int i = 1; i < argc; i++) {
        if (starts_with(argv[i], TEST_FILTER_FLAG)) {
            parse_test_filter(test_runner, argv[i]);
        }
        if (starts_with(argv[i], DEATH_TEST_FLAG)) {
            parse_death_test(test_runner, argv[i]);
        }
    }
}

void r2k_test_start(int argc, char** argv) {
    init_terminal();

    r2k_test_runner_t* test_runner = _r2k_get_test_runner();
    parse_args(test_runner, argc, argv);

    if (!string_empty(test_runner->test_filter)) {
        printf_yellow("Note: Test filter = %s\n", test_runner->test_filter);
    }

    if (test_runner->death_test.has_been_started) {
        printf_yellow("Note: Is running death test for test %s, line %d\n", test_runner->test_filter, test_runner->death_test.line_num);
    }

    printf_green("[==========] ");
    printf("Running tests.\n");

    printf_green("[----------] ");
    printf("Global test environment set-up.\n");

    test_runner->timer = r2k_timer_start();
}

r2k_test_result_t r2k_test_end() {
    r2k_test_result_t result = R2K_TEST_OK;
    r2k_test_runner_t* test_runner = _r2k_get_test_runner();
    r2k_milliseconds_t test_time = r2k_timer_stop(&test_runner->timer);

    printf_green("[----------] ");
    printf("Global test environment tear-down\n");

    printf_green("[==========] ");
    printf("%d test%s from %d test suite%s ran. (%d ms total)\n",
        test_runner->num_tests,
        plural_suffix(test_runner->num_tests),
        test_runner->num_suites,
        plural_suffix(test_runner->num_suites),
        test_time.value
    );

    printf_green("[  PASSED  ] ");
    printf("%d test%s.\n", test_runner->num_passed_tests, plural_suffix(test_runner->num_passed_tests));

    const size_t num_failed_tests = test_runner->num_failed_tests;
    if (num_failed_tests > 0) {
        printf_red("[  FAILED  ] ");
        printf("%d test%s, listed below:\n", num_failed_tests, plural_suffix(num_failed_tests));
        for (size_t i = 0; i < num_failed_tests; i++) {
            printf_red("[  FAILED  ] ");
            printf("%s\n", test_runner->failed_test_names[i]);
        }

        printf("\n %d FAILED TEST\n%s",
            num_failed_tests,
            uppercase_plural_suffix(num_failed_tests)
        );

        result = R2K_TEST_FAILED;
    }
    else {
        printf("\n");
    }

    const size_t num_disabled_tests = test_runner->num_disabled_tests;
    if (num_disabled_tests > 0) {
        printf_yellow("  YOU HAVE %d DISABLED TEST%s\n\n",
            num_disabled_tests,
            uppercase_plural_suffix(num_disabled_tests)
        );
    }

    return result;
}
