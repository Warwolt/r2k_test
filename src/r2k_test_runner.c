#include "r2k_test/r2k_test_runner.h"

#include <assert.h>

static r2k_test_runner_t g_test_runner;

void _r2k_internal_init_test_runner() {
    g_test_runner = (r2k_test_runner_t) {
        .num_tests = 0,
        .num_suites = 0,
        .num_passed = 0,
        .num_failed = 0,
        .total_milliseconds = 0,
    };
}

r2k_test_runner_t* _r2k_internal_get_test_runner() {
    return &g_test_runner;
}
