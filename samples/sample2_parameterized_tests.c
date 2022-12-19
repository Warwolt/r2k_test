#include <r2k_test/r2k_test.h>

typedef struct int_pair {
    int x;
    int y;
} int_pair_t;

void arithmetic_tests(void) {
    TEST_SUITE_START();

    TEST_P(addition_is_commutative, int_pair_t, {1,2}, {2,3}, {3,4}) {
        int x = get_param().x;
        int y = get_param().y;
        EXPECT_EQ(x + y, y + x);
    }

    TEST_P(zero_is_additive_identity, int, 1, 2, 3) {
        int num = get_param();
        EXPECT_EQ(num + 0, num);
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    arithmetic_tests();

    return r2k_test_end();
}
