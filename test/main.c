#include "r2k_test/r2k_test.h"

#include <string.h>
#include <sys\timeb.h>

void dummy_tests(void) {
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

    TEST(expect_true) {
        bool five_is_even = 5 % 2 == 0;
        EXPECT_TRUE(five_is_even);
    }

    TEST_SUITE_END();
}

void other_tests(void) {
    TEST_SUITE_START();

    TEST(DISABLED_strcmp_equal_strings) {
        EXPECT_TRUE(strcmp("aaa", "aaa") == 0);
    }

    TEST(strcmp_unequal_strings) {
        EXPECT_TRUE(strcmp("aaa", "bbb") == 0);
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    dummy_tests();
    other_tests();

    return r2k_test_end();
}
