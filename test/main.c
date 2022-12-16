#include "r2k_test/r2k_test.h"

#include "r2k_test/internal/r2k_string_util.h"

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

    TEST_SUITE_END();
}

int main(int argc, char **argv) {
    if (argc > 0) {
        char filter_prefix[100] = { 0 };
        if (starts_with(argv[1], "--test_filter=")) {
            size_t prefix_len = strlen("--test_filter=");
            const char* arg_value = argv[1] + prefix_len;
            if (arg_value != '\0') {
                strncpy(filter_prefix, arg_value, 100);
            }
            printf("%s\n", filter_prefix);
        }
    }

    if (0) {
        r2k_test_start();

        dummy_tests();

        return r2k_test_end();
    }
}
