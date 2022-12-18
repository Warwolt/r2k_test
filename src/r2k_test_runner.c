#include "r2k_test/r2k_test_runner.h"

#include <assert.h>

static r2k_test_runner_t g_test_runner;

r2k_test_runner_t* _r2k_get_test_runner() {
    return &g_test_runner;
}
