#ifndef R2K_TEST_H
#define R2K_TEST_H

#include "test_assert.h"

#include <stddef.h>

typedef struct r2k_test_runner {
    size_t num_tests;
    size_t num_suites;
    size_t num_milliseconds;
} r2k_test_runner_t;

r2k_test_runner_t r2k_test_start(void);
void r2k_test_end(const r2k_test_runner_t* runner);

#endif // R2K_TEST_H
