#include "r2k_test/r2k_test.h"

void dummy_tests() {
    TEST_SUITE_START();

    TEST(expect_integers_ok) {
        EXPECT_EQ(2 + 2, 4);
    }

    TEST(expect_integers_fail) {
        EXPECT_EQ(2 + 2, 5);
    }

    TEST(expect_chars) {
        EXPECT_CHAR_EQ('A', 'a');
    }

    TEST(expect_pointers) {
        int a, b;
        EXPECT_PTR_EQ(&a, &b);
    }

    TEST(expect_strings) {
        EXPECT_STR_EQ("foo", "bar");
    }

    TEST(expect_float) {
        EXPECT_FLOAT_NEAR(1.0f, 2.0f, 0.01);
    }

    TEST(expect_double) {
        EXPECT_DOUBLE_NEAR(1.0, 2.01, 0.01);
    }

    TEST_SUITE_END();
}

int main(void) {
    r2k_test_start();

    dummy_tests();

    return r2k_test_end();
}
