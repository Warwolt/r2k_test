#ifndef R2K_STRING_UTIL_H
#define R2K_STRING_UTIL_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define string_empty(str) (str && *str == '\0')

typedef struct str_slice {
    const char* str; // start of slice
    size_t len; // slice length
} str_slice_t;

bool starts_with(const char* restrict str, const char* restrict prefix);

// returns true if pattern exactly matches str, or matches up until first '*'
bool asterix_match(const char* pattern, const char* str);
bool asterix_match_substr(const char* pattern, const char* str, size_t len);

// takes a brace list string, e.g. "{{1,2}, {3,4}}" and returns one value in the list
str_slice_t get_brace_list_value(const char* brace_list_str, size_t index);

#endif // R2K_STRING_UTIL_H
