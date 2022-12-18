#include "test/string_util_tests.h"

#include <r2k_test/r2k_test.h>
#include "r2k_test/internal/r2k_string_util.h"

void string_util_tests() {
    TEST_SUITE_START();

    TEST(no_strings_starts_with_empty_string) {
        EXPECT_TRUE(starts_with("abc", ""));
    }

    TEST(no_string_is_prefix_to_empty_string) {
        EXPECT_FALSE(starts_with("", "abc"));
    }

    TEST(string_hello_starts_with_h) {
        EXPECT_TRUE(starts_with("hello", "h"));
    }

    TEST(string_teater_starts_with_tea) {
        EXPECT_TRUE(starts_with("teater", "tea"));
    }



    TEST_SUITE_END();
}

