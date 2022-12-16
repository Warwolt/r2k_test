#ifndef R2K_TEST_CASE_H
#define R2K_TEST_CASE_H

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

void r2k_test_case_start(r2k_test_suite_t* suite, const char* case_name);
void r2k_test_case_end(r2k_test_suite_t* suite);

#endif // R2K_TEST_CASE_H
