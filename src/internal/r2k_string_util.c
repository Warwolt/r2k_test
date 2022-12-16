#include "r2k_test/internal/r2k_string_util.h"

bool starts_with(const char* restrict string, const char* restrict prefix) {
    return strncmp(prefix, string, strlen(prefix)) == 0;
}

// returns true if either lhs == rhs or matches up until asterix
// FIXME: this should fail if prefix is longer than string
bool wildcard_prefix_match(const char* prefix, const char* string) {
    while (*prefix && *string) {
        if (*prefix == '*') {
            return true; // prefix matches
        }
        if (*prefix != *string) {
            return false; // not matching
        }
        prefix++;
        string++;
    }

    return true;
}
