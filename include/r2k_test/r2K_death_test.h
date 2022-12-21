#ifndef R2K_DEATH_TEST_H
#define R2K_DEATH_TEST_H

#include <r2k_test/r2k_test_runner.h>
#include <r2k_test/r2k_test_suite.h>

#include <stdbool.h>
#include <stdio.h>

typedef enum r2k_death_test_outcome {
    R2K_DEATH_TEST_OK,
    R2K_DEATH_TEST_FAILED_TO_DIE,
    R2K_DEATH_TEST_UNEXPECTED_EXIT_CODE,
    R2K_DEATH_TEST_UNEXPECTED_ERROR_MSG,
} r2k_death_test_outcome_t;

void r2k_run_death_test(int line_number, const char* executable_path, r2k_test_suite_t* suite);
void r2k_fail_death_test_run(r2k_test_runner_t* test_runner);
r2k_death_test_outcome_t r2k_get_death_test_outcome(const r2k_death_test_result_t* death_test, const unsigned long expected_exit_code, const char* stderr_regex);
void r2k_print_death_test_stderr(const char* stderr_output);

/**
 * Run a death test with an expected exit code
 *
 * @param statement the statement that should cause a program termination
 * @param expected_exit_code the value of the exit code the statement should cause
 * @param stderr_regex regex used for matching the error message of the statement
 */
#define EXPECT_EXIT(statement, expected_exit_code, stderr_regex) \
    /* Run the death test itself */ \
    if (_r2k_get_test_runner()->death_test.has_been_started) { \
        if (_r2k_get_test_runner()->death_test.line_num == __LINE__) { \
            statement; \
            r2k_fail_death_test_run(_r2k_get_test_runner()); \
        } \
    /* Start death test and then report the result */ \
    } else { \
        R2K_TEST_SUITE.current_test.death_test_result = (r2k_death_test_result_t) {0}; \
        r2k_run_death_test(__LINE__, _r2k_get_test_runner()->death_test.executable_path, &R2K_TEST_SUITE); \
        r2k_death_test_outcome_t outcome = r2k_get_death_test_outcome(&R2K_TEST_SUITE.current_test.death_test_result, expected_exit_code, stderr_regex); \
        if (outcome != R2K_DEATH_TEST_OK) { \
            printf("%s(%d): error: Death test: %s\n", __FILE__, __LINE__, #statement); \
            R2K_TEST_SUITE.current_test.successful = false; \
        } \
        switch (outcome) { \
            case R2K_DEATH_TEST_OK: \
                break; \
            case R2K_DEATH_TEST_FAILED_TO_DIE: \
                printf("    Result: failed to die.\n"); \
                printf(" Error msg:\n"); \
                r2k_print_death_test_stderr(R2K_TEST_SUITE.current_test.death_test_result.stderr_output); \
                break; \
            case R2K_DEATH_TEST_UNEXPECTED_EXIT_CODE: \
                printf("    Result: died but not with expected exit code:\n"); \
                printf("            Exited with exit status %lu\n", R2K_TEST_SUITE.current_test.death_test_result.exit_code); \
                printf(" Actual msg:\n"); \
                r2k_print_death_test_stderr(R2K_TEST_SUITE.current_test.death_test_result.stderr_output); \
                break; \
            case R2K_DEATH_TEST_UNEXPECTED_ERROR_MSG: \
                printf("    Result: died but not with expected error.\n"); \
                printf("  Expected: contains regular expression \"%s\"\n", stderr_regex); \
                printf(" Actual msg:\n"); \
                r2k_print_death_test_stderr(R2K_TEST_SUITE.current_test.death_test_result.stderr_output); \
                break; \
        } \
    }

#endif // R2K_DEATH_TEST_H
