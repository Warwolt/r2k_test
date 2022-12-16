#include "r2k_test/internal/r2k_string_util.h"

bool starts_with(const char* restrict string, const char* restrict prefix) {
    return strncmp(prefix, string, strlen(prefix)) == 0;
}

// returns true if either lhs == rhs or matches up until asterix
bool wild_card_match(const char* lhs, const char* rhs) {
    while (*lhs && *rhs) {
        if (*lhs == '*') {
            return true; // prefix matches
        }
        if (*lhs != *rhs) {
            return false; // not matching
        }
        lhs++;
        rhs++;
    }
    return true;
}
