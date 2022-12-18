#ifndef R2K_TEST_SUITE_H
#define R2K_TEST_SUITE_H

#include <r2k_test/r2k_test_runner.h>
#include <r2k_test/internal/r2k_timer.h>

#include <stdbool.h>
#include <stddef.h>

typedef struct r2k_test_case {
    const char* name;
    bool successful;
    bool skipped;
    r2k_timer_t timer;
} r2k_test_case_t;

typedef struct r2k_test_suite {
    r2k_test_runner_t* test_runner;
    const char* name;
    size_t num_ran_tests;
    r2k_timer_t timer;
    r2k_test_case_t current_test;
} r2k_test_suite_t;

bool r2k_should_skip_suite(const char* suite_name, const char* test_filter);
r2k_test_suite_t r2k_test_suite_start(const char* suite_name);
void r2k_test_suite_end(r2k_test_suite_t* suite);
bool r2k_test_case_start(r2k_test_suite_t* suite, const char* test_name);
void r2k_test_case_end(r2k_test_suite_t* suite);

#define R2K_TEST_SUITE g_test_suite
#define TEST_SUITE_START() if (r2k_should_skip_suite(__func__, _r2k_get_test_runner()->test_filter)) return; r2k_test_suite_t R2K_TEST_SUITE = r2k_test_suite_start(__func__)
#define TEST_SUITE_END() r2k_test_suite_end(&R2K_TEST_SUITE)
#define TEST(test_name) for (bool start = r2k_test_case_start(&R2K_TEST_SUITE, #test_name); start; start = false)

#endif // R2K_TEST_SUITE_H
