#include <r2k_test/r2k_test.h>

#include "test/internal_tests.h"

void arithmetic_tests(void) {
    TEST_SUITE_START();

    TEST(addition_is_commutative) {
        EXPECT_EQ(2 + 3, 3 + 2);
    }

    TEST(zero_is_additive_identity) {
        EXPECT_EQ(2 + 0, 2);
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    // arithmetic_tests();
    internal_tests();

    return r2k_test_end();
}
