#include "test/internal_tests.h"

#include "r2k_test/r2k_test.h"
#include "r2k_test/r2k_test_suite.h"
#include "r2k_test/internal/r2k_string_util.h"

void string_util_tests(void) {
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

void test_suite_tests(void) {
    TEST_SUITE_START();

    TEST(suite_skipped_if_suite_name_differs_from_filter) {
        EXPECT_TRUE(r2k_should_skip_suite("foo_suite", "some_filter"));
    }

    TEST(suite_not_skipped_if_test_filter_empty) {
        EXPECT_FALSE(r2k_should_skip_suite("foo_suite", ""));
    }

    TEST(suite_not_skipped_if_suite_name_exactly_matches_filter) {
        EXPECT_FALSE(r2k_should_skip_suite("foo_suite", "foo_suite"));
    }

    TEST(suite_not_skipped_if_suite_name_is_prefix_of_filter) {
        EXPECT_FALSE(r2k_should_skip_suite("foo_suite", "foo_suite.bar_test"));
    }

    TEST_SUITE_END();
}

void internal_tests(void) {
    string_util_tests();
    test_suite_tests();
}
