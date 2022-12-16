#ifndef R2K_TEST_H
#define R2K_TEST_H

#include "r2k_test/r2k_test_assert.h"
#include "r2k_test/r2k_test_runner.h"
#include "r2k_test/r2k_test_suite.h"

#include <stddef.h>
#include <stdbool.h>

typedef enum r2k_test_result {
    R2K_TEST_OK = 0,
    R2K_TEST_FAILED = 1,
} r2k_test_result_t;

void r2k_test_start(void);
r2k_test_result_t r2k_test_end();

#endif // R2K_TEST_H
