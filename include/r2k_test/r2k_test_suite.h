#ifndef R2K_TEST_SUITE_H
#define R2K_TEST_SUITE_H

#include "r2k_test/r2k_test_runner.h"

typedef struct r2k_test_suite {
    r2k_test_runner_t* test_runner;
    const char* name;
    size_t num_ran_tests;
    r2k_test_case_t current_test;
} r2k_test_suite_t;

r2k_test_suite_t r2k_test_suite_start(void);
void r2k_test_suite_end(r2k_test_suite_t* suite);

#endif // R2K_TEST_SUITE_H
