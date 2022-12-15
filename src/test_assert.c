#include "r2k_test/test_assert.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool check_float_near(float actual, float expected, float abs_error, char* actual_str, char* expected_str, int buf_len) {
    if (abs(actual - expected) > abs_error) {
        snprintf(actual_str, buf_len, "%f", actual);
        snprintf(expected_str, buf_len, "%f", expected);
        return false;
    }
    return true;
}
