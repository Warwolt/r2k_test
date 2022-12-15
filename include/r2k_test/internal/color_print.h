#ifndef R2K_TEST_COLOR_PRINT_H
#define R2K_TEST_COLOR_PRINT_H

#include <stdio.h>

#define TEST_COLOR_GREEN "\033[32m"
#define TEST_COLOR_RED "\033[31m"
#define TEST_COLOR_RESET "\033[0m"

#define printf_green(...) \
    printf("%s", TEST_COLOR_GREEN); \
    printf(__VA_ARGS__); \
    printf("%s", TEST_COLOR_RESET)

#define printf_red(...) \
    printf("%s", TEST_COLOR_RED); \
    printf(__VA_ARGS__); \
    printf("%s", TEST_COLOR_RESET)

#endif // R2K_TEST_COLOR_PRINT_H
