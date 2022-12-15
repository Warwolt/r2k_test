#include "r2k_test/r2k_test.h"
#include "r2k_test/internal/r2k_color_print.h"
#include "r2k_test/internal/r2k_print_util.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TEST_SUITE_START() \
    test_suite_t g_suite = (test_suite_t) { \
        .test_runner = _r2k_internal_get_test_runner(), \
        .name = __func__, \
        .num_ran_tests = 0, \
        .current_test = { \
            .suite = __func__, \
            .name = NULL, \
            .successful = false, \
        }, \
    }; \
    g_suite.test_runner->num_suites += 1; \
    printf_green("[----------] "); \
    printf("Running tests from %s\n", __func__)


#define TEST_SUITE_END() \
    r2k_print_case_result(&g_suite.current_test); \
    printf_green("[----------] "); \
    printf("%d test%s from %s (0 ms total)\n\n", \
        g_suite.num_ran_tests, \
        plural_suffix(g_suite.num_ran_tests), \
        g_suite.name \
    )

#define TEST(test_name) r2k_test_case_start(&g_suite, #test_name);

void dummy_tests() {
    TEST_SUITE_START();

    TEST(expect_integers) {
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

    r2k_test_end();
    return 0;
}
