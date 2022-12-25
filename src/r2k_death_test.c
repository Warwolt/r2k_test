#include <r2k_test/r2K_death_test.h>

#include <r2k_test/internal/r2k_string_util.h>
#include <r2k_test/internal/r2k_arraylen.h>
#ifdef WIN32
#include <r2k_test/internal/r2k_death_test_win32.h>
#endif

#include <tiny-regex-c/re.h>

#include <string.h>
#include <stdio.h>
#include <string.h>

/**
 * Starts a subprocess that runs the EXPECT_EXIT at the given line number
 *
 * @param line_number the line number of the EXPECT_EXIT macro
 * @param executable_path the value of argv[0] in the cmd line
 * @param[out] suite the test suite running the death test
 */
void r2k_run_death_test(int line_number, const char* executable_path, r2k_test_suite_t* suite) {
#ifdef WIN32
    run_death_test_win32(line_number, executable_path, suite);
#else
    #error run_death_test not implemented for POSIX yet!
#endif
}

void r2k_fail_death_test_run(r2k_test_runner_t* test_runner) {
#ifdef WIN32
    fail_death_test_run_win32(test_runner);
#else
    #error r2k_fail_death_test_run not implemented for POSIX yet!
#endif
}

r2k_death_test_outcome_t r2k_get_death_test_outcome(const r2k_death_test_result_t* death_test, const unsigned long expected_exit_code, const char* stderr_regex) {
    if (death_test->statement_did_not_terminate) {
        return R2K_DEATH_TEST_FAILED_TO_DIE;
    }

    if (death_test->exit_code != expected_exit_code) {
        return R2K_DEATH_TEST_UNEXPECTED_EXIT_CODE;
    }

    int match_length; // can this be passed as NULL instead?
    if (re_match(stderr_regex, death_test->stderr_output, &match_length) == -1) {
        return R2K_DEATH_TEST_UNEXPECTED_ERROR_MSG;
    }

    return R2K_DEATH_TEST_OK;
}

void r2k_print_death_test_stderr(const char* stderr_output) {
    int i = 0;
    char current_line[512];
    for (const char* scan = stderr_output; *scan; scan++) {
        current_line[i] = *scan;
        /* Print current line */
        if (*scan == '\n') {
            current_line[i+1] = '\0';
            printf("[  DEATH   ] %s", current_line);
            i = 0;
        /* Print last line, missing trailing '\n' */
        } else if (*(scan + 1) == '\0') {
            current_line[i+1] = '\0';
            printf("[  DEATH   ] %s\n", current_line);
        /* Continue scanning */
        } else {
            i++;
        }
    }
}
