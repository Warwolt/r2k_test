#include "test/internal_tests.h"

#include "r2k_test/r2k_test.h"
#include "r2k_test/r2k_test_suite.h"
#include "r2k_test/internal/r2k_string_util.h"

#include <string.h>

void starts_with_tests(void) {
    TEST_SUITE_START();

    TEST(every_strings_starts_with_empty_string) {
        EXPECT_TRUE(starts_with("abc", ""));
        EXPECT_TRUE(starts_with("hello", ""));
        EXPECT_TRUE(starts_with("world", ""));
    }

    TEST(no_string_is_prefix_to_empty_string) {
        EXPECT_FALSE(starts_with("", "abc"));
        EXPECT_FALSE(starts_with("", "hello"));
        EXPECT_FALSE(starts_with("", "world"));
    }

    TEST(strings_start_with_substrings_of_themselves) {
        EXPECT_TRUE(starts_with("hello", "h"));
        EXPECT_TRUE(starts_with("world", "wo"));
        EXPECT_TRUE(starts_with("teater", "tea"));
    }

    TEST_SUITE_END();
}

void asterix_match_tests(void) {
    TEST_SUITE_START();

    /**
     * asterix_match
     */
    TEST(identical_strings_match) {
        EXPECT_TRUE(asterix_match("cup", "cup"));
        EXPECT_TRUE(asterix_match("bread", "bread"));
        EXPECT_TRUE(asterix_match("pizza", "pizza"));
    }

    TEST(single_asterix_matches_any_string) {
        EXPECT_TRUE(asterix_match("*", "abc"));
        EXPECT_TRUE(asterix_match("*", "hello"));
        EXPECT_TRUE(asterix_match("*", "world"));
    }

    TEST(pattern_shorter_than_string_does_not_match) {
        EXPECT_FALSE(asterix_match("cup", "cupcake"));
        EXPECT_FALSE(asterix_match("bread", "breadsticks"));
        EXPECT_FALSE(asterix_match("pizza", "pizza pie"));
    }

    TEST(pattern_longer_than_string_does_not_match) {
        EXPECT_FALSE(asterix_match("cupcake", "cup"));
        EXPECT_FALSE(asterix_match("breadsticks", "bread"));
        EXPECT_FALSE(asterix_match("pizza pie", "pizza"));
    }

    /**
     * asterix_match_substr
     */
    TEST(single_asterix_matches_any_substring) {
        EXPECT_TRUE(asterix_match_substr("*", "cupcake", strlen("cup")));
        EXPECT_TRUE(asterix_match_substr("*", "breadsticks", strlen("bread")));
        EXPECT_TRUE(asterix_match_substr("*", "pizza pie", strlen("pizza")));
    }

    TEST(pattern_can_match_substring_exactly) {
        EXPECT_TRUE(asterix_match_substr("cup", "cupcake", strlen("cup")));
        EXPECT_TRUE(asterix_match_substr("bread", "breadsticks", strlen("bread")));
        EXPECT_TRUE(asterix_match_substr("pizza", "pizza pie", strlen("pizza")));
    }

    TEST(pattern_shorter_than_substring_does_not_match) {
        EXPECT_FALSE(asterix_match_substr("c", "cupcake", strlen("cup")));
        EXPECT_FALSE(asterix_match_substr("br", "breadsticks", strlen("bread")));
        EXPECT_FALSE(asterix_match_substr("piz", "pizza pie", strlen("pizza")));
    }

    TEST(pattern_with_asterix_shorter_than_substring_does_match) {
        EXPECT_TRUE(asterix_match_substr("c*", "cupcake", strlen("cup")));
        EXPECT_TRUE(asterix_match_substr("br*", "breadsticks", strlen("bread")));
        EXPECT_TRUE(asterix_match_substr("piz*", "pizza pie", strlen("pizza")));
    }

    TEST(pattern_longer_than_substring_does_not_match) {
        EXPECT_FALSE(asterix_match_substr("cup", "cupcake", strlen("c")));
        EXPECT_FALSE(asterix_match_substr("bread", "breadsticks", strlen("br")));
        EXPECT_FALSE(asterix_match_substr("pizza", "pizza pie", strlen("piz")));
    }

    TEST_SUITE_END();
}

void string_util_tests(void) {
    starts_with_tests();
    asterix_match_tests();
}

void test_suite_tests(void) {
    // can't use TEST_SUITE_START() since we're testing r2k_should_skip_suite
    r2k_test_suite_t R2K_TEST_SUITE = r2k_test_suite_start(__func__);

    TEST(suite_skipped_if_suite_name_differs_from_filter) {
        EXPECT_TRUE(r2k_should_skip_suite("foo_suite", "some_filter"));
    }

    TEST(suite_skipped_if_suite_name_differs_from_filter_with_asterix) {
        EXPECT_TRUE(r2k_should_skip_suite("foo_suite", "some_*"));
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

    TEST(suite_not_skipped_if_filter_matches_suite_name_until_asterix) {
        EXPECT_FALSE(r2k_should_skip_suite("foo_suite", "foo*"));
    }

    TEST_SUITE_END();
}

void internal_tests(void) {
    string_util_tests();
    test_suite_tests();
}
