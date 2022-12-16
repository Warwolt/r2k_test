#ifndef R2K_STRING_UTIL_H
#define R2K_STRING_UTIL_H

#include <stdbool.h>
#include <string.h>

#define string_empty(str) (str && *str == '\0')

bool starts_with(const char* restrict string, const char* restrict prefix);
bool wildcard_prefix_match(const char* prefix, const char* string);

#endif // R2K_STRING_UTIL_H
