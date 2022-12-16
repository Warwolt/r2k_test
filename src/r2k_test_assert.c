#include "r2k_test/r2k_test_assert.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool r2k_check_int_eq(int actual, int expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "%d", actual);
        snprintf(expected_str, buf_len, "%d", expected);
        return false;
    }
    return true;
}

bool r2k_check_char_eq(char actual, char expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "%c", actual);
        snprintf(expected_str, buf_len, "%c", expected);
        return false;
    }
    return true;
}

bool r2k_check_ptr_eq(void* actual, void* expected, char* actual_str, char* expected_str, int buf_len) {
    if (actual != expected) {
        snprintf(actual_str, buf_len, "0x%p", actual);
        snprintf(expected_str, buf_len, "0x%p", expected);
        return false;
    }
    return true;
}

bool r2k_check_str_eq(const char* actual, const char* expected, char* actual_str, char* expected_str, int buf_len) {
    if (strcmp(actual, expected) != 0) {
        snprintf(actual_str, buf_len, "\"%s\"", actual);
        snprintf(expected_str, buf_len, "\"%s\"", expected);
        return false;
    }
    return true;
}

bool r2k_check_float_near(float actual, float expected, float abs_error, char* diff_str, char* actual_str, char* expected_str, int buf_len) {
    float diff = abs(actual - expected);
    if (diff > abs_error) {
        snprintf(diff_str, buf_len, "%f", diff);
        snprintf(actual_str, buf_len, "%f", actual);
        snprintf(expected_str, buf_len, "%f", expected);
        return false;
    }
    return true;
}

bool r2k_check_double_near(double actual, double expected, float abs_error, char* diff_str, char* actual_str, char* expected_str, int buf_len) {
    double diff = abs(actual - expected);
    if (diff > abs_error) {
        snprintf(diff_str, buf_len, "%f", diff);
        snprintf(actual_str, buf_len, "%f", actual);
        snprintf(expected_str, buf_len, "%f", expected);
        return false;
    }
    return true;
}
