#ifndef R2K_TEST_RUNNER_H
#define R2K_TEST_RUNNER_H

#include <stddef.h>

typedef struct r2k_test_runner {
    size_t num_tests;
    size_t num_suites;
    size_t num_milliseconds;
} r2k_test_runner_t;

void _r2k_internal_init_test_runner();
r2k_test_runner_t* _r2k_internal_get_test_runner();

#endif // R2K_TEST_RUNNER_H
