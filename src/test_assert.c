#include "r2k_test/test_assert.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool check_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "%d", actual);
        snprintf(expected_str, buf_len, "%d", expected);
        return false;
    }
    return true;
}

bool check_char_eq(char actual, char expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "%c (%d)", actual, actual);
        snprintf(expected_str, buf_len, "%c (%d)", expected, expected);
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
