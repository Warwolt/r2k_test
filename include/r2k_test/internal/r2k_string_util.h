#ifndef R2K_STRING_UTIL_H
#define R2K_STRING_UTIL_H

#include <stdbool.h>
#include <string.h>

#define string_empty(str) (str && *str == '\0')

bool starts_with(const char* restrict str, const char* restrict prefix);
// returns true if pattern exactly matches str, or matches up until first '*'
bool asterix_match(const char* pattern, const char* str);
bool asterix_match_substr(const char* pattern, const char* str, size_t len);

#endif // R2K_STRING_UTIL_H
