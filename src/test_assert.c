#include "r2k_test/test_assert.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool check_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        if (isprint(actual)) {
            snprintf(actual_str, buf_len, "%d ('%c')", actual, actual);
        } else {
            snprintf(actual_str, buf_len, "%d", actual);
        }
        if (isprint(expected)) {
            snprintf(expected_str, buf_len, "%d ('%c')", expected, expected);
        } else {
            snprintf(expected_str, buf_len, "%d", expected);
        }
        return false;
    }
    return true;
}

bool check_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "0x%p", actual);
        snprintf(expected_str, buf_len, "0x%p", expected);
        return false;
    }
    return true;
}
