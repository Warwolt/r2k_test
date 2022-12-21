#include <r2k_test/internal/r2k_string_util.h>

#include <limits.h>
#include <ctype.h>

bool string_empty(const char* str) {
    return str && *str == '\0';
}

bool is_number(const char* str) {
    if (string_empty(str)) {
        return false;
    }

    for (; *str; str++) {
        if (!isdigit(*str)) {
            return false;
        }
    }

    return true;
}

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

// Note: Since this is only intended to be used internally, it only handles
// happy paths in the brace list. Bad input will give bad behavior!
str_slice_t get_brace_list_value(const char const* brace_list_str, size_t index) {
    if (string_empty(brace_list_str)) {
        return (str_slice_t) {
            .str = "",
            .len = 0,
        };
    }

    // scan through list for start of value
    int brace_nest_depth = 0;
    size_t num_commas = 0;
    size_t str_len = 0;
    const char* str = brace_list_str;
    for (const char* scan = brace_list_str; *scan; scan++) {
        // don't grab commas within a pair of braces
        if (*scan == '{') {
            brace_nest_depth++;
        }
        if (*scan == '}') {
            brace_nest_depth--;
        }
        // if comma, set str to next start of value
        bool is_within_brace_group = brace_nest_depth > 0;
        if (*scan == ',' && !is_within_brace_group) {
            num_commas++;
            // check if we've found end of requsted value
            if (num_commas == index + 1) {
                break;
            }
            str = scan + 1; // move past the comma
            str_len = 0;
        } else {
            str_len++;
        }
    }

    // trim spaces before value
    size_t leading_spaces = 0;
    while(*str) {
        if (*str != ' ') {
            break;
        }
        str++;
        leading_spaces++;
    }
    str_len -= leading_spaces;

    // trim spaces after value
    size_t trailing_spaces = 0;
    const char* scan = str + (str_len - 1);
    for (size_t i = 0; i < str_len; i++) {
        if (*scan != ' ') {
            break;
        }
        trailing_spaces++;
        scan--;
    }
    str_len -= trailing_spaces;

    return (str_slice_t) {
        .str = str,
        .len = str_len,
    };
}
