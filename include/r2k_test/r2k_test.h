#ifndef R2K_TEST_H
#define R2K_TEST_H

#include "r2k_test/r2k_test_assert.h"
#include "r2k_test/r2k_test_runner.h"

#include <stddef.h>

typedef struct test_case {
    const char* suite;
    const char* name;
    bool successful;
} test_case_t;

typedef struct test_suite {
    r2k_test_runner_t* test_runner;
    const char* name;
    size_t num_ran_tests;
    test_case_t current_test;
} test_suite_t;

void r2k_test_start(void);
void r2k_test_end();

void r2k_test_case_start(test_suite_t* suite, const char* case_name);
void r2k_test_case_end(const test_case_t* test);

#endif // R2K_TEST_H
