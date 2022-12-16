#include "r2k_test/internal/r2k_string_util.h"

bool starts_with(const char* restrict string, const char* restrict prefix) {
    return strncmp(prefix, string, strlen(prefix)) == 0;
}

