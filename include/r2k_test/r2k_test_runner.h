#ifndef R2K_TEST_RUNNER_H
#define R2K_TEST_RUNNER_H

#include "r2k_test/internal/r2k_timer.h"

#include <stddef.h>

#define R2K_MAX_NUM_FAILED_TEST_STR 100
#define R2K_MAX_FAILED_TEST_STR_LEN 100
#define R2K_MAX_TEST_FILTER_LEN 100

typedef struct r2k_test_runner {
    size_t num_tests;
    size_t num_suites;
    size_t num_passed_tests;
    size_t num_failed_tests;
    size_t num_disabled_tests;
    char failed_test_names[R2K_MAX_NUM_FAILED_TEST_STR][R2K_MAX_FAILED_TEST_STR_LEN];
    char test_filter[R2K_MAX_TEST_FILTER_LEN];
    r2k_timer_t timer;
} r2k_test_runner_t;

r2k_test_runner_t* r2k_internal_get_test_runner();

#endif // R2K_TEST_RUNNER_H
