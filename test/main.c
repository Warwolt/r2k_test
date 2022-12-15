// TODO:
// [x] Print start and end of test suite
// [ ] 1 suite with 1 case
// [ ] 1 passing test
// [ ] 1 failing test with EXPECT_EQ
// [ ] print args to EXPECT_EQ on failure

#include "r2k_test/r2k_test.h"

#include <stdio.h>

int main(void) {
    r2k_test_runner_t runner = r2k_test_start();
    r2k_test_end(&runner);
    return 0;
}
