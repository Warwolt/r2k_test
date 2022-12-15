#include "r2k_test/test_assert.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool expect_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "%d", actual);
        snprintf(expected_str, buf_len, "%d", expected);
        return false;
    }
    return true;
}

bool expect_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "0x%p", actual);
        snprintf(expected_str, buf_len, "0x%p", expected);
        return false;
    }
    return true;
}
