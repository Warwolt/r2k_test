#ifndef R2K_TEST_WINDOWS_H
#define R2K_TEST_WINDOWS_H

#include <windows.h>
#include <stdbool.h>

// consoleapi.h
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif // ENABLE_VIRTUAL_TERMINAL_PROCESSING

// Needed for color output on Windows
bool enable_windows_virtual_terminal(void)
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return false;
    }

    return true;
}

#endif // R2K_TEST_WINDOWS_H
