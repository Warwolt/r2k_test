#include "r2k_test/r2k_test.h"

#include <stdio.h>

int main(void) {
    r2k_test_runner_t runner = r2k_test_start();
    r2k_test_end(&runner);
    return 0;
}
