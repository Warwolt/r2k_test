#ifndef R2K_TEST_SUITE_H
#define R2K_TEST_SUITE_H

#include <r2k_test/r2k_test_runner.h>
#include <r2k_test/internal/r2k_timer.h>

#include <stdbool.h>
#include <stddef.h>

#define DEATH_TEST_STDERR_LEN 4096

typedef struct death_test_result {
    bool statement_did_not_terminate;
    unsigned long exit_code;
    char stderr_output[DEATH_TEST_STDERR_LEN];
} r2k_death_test_result_t;

typedef struct r2k_test_case {
    const char* name;
    bool successful;
    bool skipped;
    r2k_timer_t timer;
    // used for parameterized tests:
    bool is_parameterized;
    size_t iter;
    const char* parameter_list;
    // used for death tests:
    r2k_death_test_result_t death_test_result;
} r2k_test_case_t;

typedef struct r2k_test_suite {
    r2k_test_runner_t* test_runner;
    const char* name;
    size_t num_ran_tests;
    r2k_timer_t timer;
    r2k_test_case_t current_test;
} r2k_test_suite_t;

r2k_test_suite_t r2k_test_suite_start(const char* suite_name);
void r2k_test_suite_end(r2k_test_suite_t* suite);
bool r2k_test_case_start(r2k_test_suite_t* suite, const char* test_name);
void r2k_test_case_end(r2k_test_suite_t* suite);
bool r2k_param_test_case_start(r2k_test_suite_t* suite, const char* test_name, size_t test_iter);
void r2k_param_test_case_end(r2k_test_suite_t* suite, size_t test_iter);
bool r2k_should_skip_suite(const char* suite_name, const char* test_filter);

#define R2K_TEST_SUITE r2k_test_suite
#define TEST_SUITE_START() \
    if (r2k_should_skip_suite(__func__, _r2k_get_test_runner()->test_filter)) \
        return; \
    r2k_test_suite_t R2K_TEST_SUITE = r2k_test_suite_start(__func__); \
    size_t r2k_index; \
    (void)(r2k_index)
#define TEST_SUITE_END() r2k_test_suite_end(&R2K_TEST_SUITE)
#define TEST(test_name) for (bool start = r2k_test_case_start(&R2K_TEST_SUITE, #test_name); start; start = false)
#define TEST_P(test_name, type, ...) \
    type test_name##_params[] = {__VA_ARGS__}; \
    R2K_TEST_SUITE.current_test.parameter_list = #__VA_ARGS__; \
    r2k_index = 0; \
    if (r2k_param_test_case_start(&R2K_TEST_SUITE, #test_name, 0)) \
        for (type r2k_param = test_name##_params[0]; r2k_index + 1 < sizeof(test_name##_params)/sizeof(test_name##_params[0]); r2k_index++, r2k_param_test_case_start(&R2K_TEST_SUITE, #test_name, r2k_index), r2k_param = test_name##_params[r2k_index])

#define get_param() r2k_param

#endif // R2K_TEST_SUITE_H
