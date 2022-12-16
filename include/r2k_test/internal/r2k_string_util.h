#ifndef R2K_STRING_UTIL_H
#define R2K_STRING_UTIL_H

#include <stdbool.h>
#include <string.h>

bool starts_with(const char* restrict string, const char* restrict prefix);
bool wild_card_match(const char* lhs, const char* rhs);

#endif // R2K_STRING_UTIL_H
