#include "r2k_test/internal/r2k_string_util.h"

#include <limits.h>

bool starts_with(const char* restrict str, const char* restrict prefix) {
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

bool asterix_match(const char* pattern, const char* str) {
    return asterix_match_substr(pattern, str, INT_MAX);
}

bool asterix_match_substr(const char* pattern, const char* str, size_t len) {
    size_t i = 0;
    while (*pattern && *str && i < len) {
        if (*pattern == '*') {
            return true; // asterix match
        }
        if (*pattern != *str) {
            return false; // no match
        }
        pattern++;
        str++;
        i++;
    }

    if (i == len && string_empty(pattern)) {
        return true; // matches substring
    }

    if (!(string_empty(str) && string_empty(pattern))) {
        return false; // not same length, so couldn't have matched
    }

    return true; // same length, so exact match
}
