#include <stdio.h>

// TODO:
// [x] Print start and end of test suite

#include "r2k_test/internal/windows.h"
#include "r2k_test/internal/color_print.h"

int main(void) {
    enable_windows_virtual_terminal();

    printf_green("[==========] ");
    printf("Running tests.\n");

    printf_green("[----------] ");
    printf("Global test environment set-up.\n");

    printf("\n");
    printf_green("[----------] ");
    printf("Global test environment tear-down\n");
    printf_green("[==========] ");
    printf("0 tests from 0 test cases ran. (0 ms total)\n");

    return 0;
}
