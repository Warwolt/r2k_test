#include <r2k_test/r2k_test.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double checked_sqrt(double x) {
    if (x < 0) {
        fprintf(stderr, "%s: cannot take square root of negative number %f\n", __func__, x);
        exit(1);
    }

    return sqrt(x);
}

void arithmetic_tests(void) {
    TEST_SUITE_START();

    TEST(taking_square_root_of_negative_number_is_an_error) {
        EXPECT_EXIT(checked_sqrt(-1), 1, "checked_sqrt: cannot take square root of negative number -1.0");
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    arithmetic_tests();

    return r2k_test_end();
}
