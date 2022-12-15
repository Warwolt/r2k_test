#include "r2k_test/r2k_test.h"
#include "r2k_test/internal/color_print.h"

#include <stdio.h>

void dummy_tests(r2k_test_runner_t* runner) {
    runner->num_suites += 1;

    printf_green("[----------] ");
    printf("Running tests from %s\n", __func__);

    {
        printf_green("[ RUN      ] ");
        printf("%s.%s\n", __func__, "hello");
        runner->num_tests += 1;

        printf_green("[       OK ] ");
        printf("%s.%s\n", __func__, "hello (0 ms)");
    }

    {
        printf_green("[ RUN      ] ");
        printf("%s.%s\n", __func__, "world");
        runner->num_tests += 1;

        printf_green("[       OK ] ");
        printf("%s.%s\n", __func__, "world (0 ms)");
    }

    printf_green("[----------] ");
    printf("1 test from %s (0 ms total)\n\n", __func__);
}

int main(void) {
    r2k_test_runner_t runner = r2k_test_start();

    dummy_tests(&runner);

    r2k_test_end(&runner);
    return 0;
}
