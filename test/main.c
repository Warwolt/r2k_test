#include <r2k_test/r2k_test.h>
#include <r2k_test/r2k_test_suite.h>
#include <r2k_test/internal/r2k_string_util.h>
#include <r2k_test/internal/r2k_arraylen.h>

#include <string.h>
#include <math.h>

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

void get_brace_list_value_tests(void) {
    TEST_SUITE_START();

    TEST(empty_list_gives_empty_substring) {
        str_slice_t slice = get_brace_list_value("", 0);
        EXPECT_TRUE(string_empty(slice.str));
        EXPECT_EQ(slice.len, 0);
    }

    TEST(single_valued_list_can_give_first_value) {
        str_slice_t slice = get_brace_list_value("a", 0);
        EXPECT_EQ_STR(slice.str, "a");
        EXPECT_EQ(slice.len, strlen("a"));
    }

    TEST(two_valued_list_can_give_second_value) {
        str_slice_t slice = get_brace_list_value("ab,cd", 1);
        EXPECT_EQ_STR(slice.str, "cd");
        EXPECT_EQ(slice.len, strlen("cd"));
    }

    TEST(three_valued_list_can_give_first_value) {
        char str[25] = { 0 };
        str_slice_t slice = get_brace_list_value("ab,cd,ef", 0);
        strncpy(str, slice.str, slice.len);

        EXPECT_EQ_STR(str, "ab");
        EXPECT_EQ(slice.len, strlen("ab"));
    }

    TEST(trims_spaces_before_value) {
        str_slice_t slice = get_brace_list_value("before, after", 1);
        EXPECT_EQ_STR(slice.str, "after");
        EXPECT_EQ(slice.len, strlen("after"));
    }

    TEST(trims_spaces_before_and_after_value) {
        char str[25] = { 0 };
        str_slice_t slice = get_brace_list_value("beginning, end ", 1);
        strncpy(str, slice.str, slice.len);

        EXPECT_EQ_STR(str, "end");
        EXPECT_EQ(slice.len, strlen("end"));
    }

    TEST(commas_inside_braces_are_ignored) {
        char str[25] = { 0 };
        str_slice_t slice = get_brace_list_value("{a,b},{c,d}", 1);
        strncpy(str, slice.str, slice.len);

        EXPECT_EQ_STR(str, "{c,d}");
        EXPECT_EQ(slice.len, strlen("{c,d}"));
    }

    TEST(braces_can_be_nested) {
        char str[25] = { 0 };
        str_slice_t slice = get_brace_list_value("{{a,b},{c,d}}, {{e,f},{g,h}}", 1);
        strncpy(str, slice.str, slice.len);

        EXPECT_EQ_STR(str, "{{e,f},{g,h}}");
        EXPECT_EQ(slice.len, strlen("{{e,f},{g,h}}"));
    }

    TEST_SUITE_END();
}

void test_suite_tests(void) {
    TEST_SUITE_START();

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

void assertion_tests(void) {
    TEST_SUITE_START();

    TEST(expect_true) {
        EXPECT_TRUE(5 > 4);
        ASSERT_TRUE(5 > 4);
    }

    TEST(expect_false) {
        EXPECT_FALSE(2 > 3);
        ASSERT_FALSE(2 > 3);
    }

    TEST(expect_eq) {
        EXPECT_EQ(2 + 2, 4);
        ASSERT_EQ(2 + 2, 4);
    }

    TEST(expect_eq_char) {
        EXPECT_EQ_CHAR('b', 'a' + 1);
        ASSERT_EQ_CHAR('b', 'a' + 1);
    }

    TEST(expect_eq_ptr) {
        int a;
        int b;
        EXPECT_EQ_PTR(&a, &b + 1);
        ASSERT_EQ_PTR(&a, &b + 1);
    }

    TEST(expect_eq_str) {
        EXPECT_EQ_STR("hello", "hello");
        ASSERT_EQ_STR("hello", "hello");
    }

    TEST(expect_near_float) {
        EXPECT_NEAR_FLOAT(0.2f + 0.1f, 0.1f + 0.1f + 0.1f, 0.001f);
        ASSERT_NEAR_FLOAT(0.2f + 0.1f, 0.1f + 0.1f + 0.1f, 0.001f);
    }

    TEST(expect_near_double) {
        EXPECT_NEAR_FLOAT(0.2 + 0.1, 0.1 + 0.1 + 0.1, 0.001);
        ASSERT_NEAR_FLOAT(0.2 + 0.1, 0.1 + 0.1 + 0.1, 0.001);
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    // r2k_string_util
    starts_with_tests();
    asterix_match_tests();
    get_brace_list_value_tests();

    test_suite_tests();
    assertion_tests();

    return r2k_test_end();
}
