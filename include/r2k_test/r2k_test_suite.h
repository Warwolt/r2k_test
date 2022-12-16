#ifndef R2K_TEST_SUITE_H
#define R2K_TEST_SUITE_H

#include "r2k_test/r2k_test_runner.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct r2k_test_case {
    const char* name;
    bool successful;
} r2k_test_case_t;

typedef struct r2k_test_suite {
    r2k_test_runner_t* test_runner;
    const char* name;
    size_t num_ran_tests;
    r2k_test_case_t current_test;
} r2k_test_suite_t;

r2k_test_suite_t r2k_test_suite_start(void);
void r2k_test_suite_end(r2k_test_suite_t* suite);
void r2k_test_case_start(r2k_test_suite_t* suite, const char* case_name);
void r2k_test_case_end(r2k_test_suite_t* suite);

#define _R2K_TEST_SUITE g_test_suite
#define TEST_SUITE_START() r2k_test_suite_t _R2K_TEST_SUITE = r2k_test_suite_start()
#define TEST_SUITE_END() r2k_test_suite_end(&_R2K_TEST_SUITE)
#define TEST(test_name) r2k_test_case_start(&_R2K_TEST_SUITE, #test_name);

#endif // R2K_TEST_SUITE_H
