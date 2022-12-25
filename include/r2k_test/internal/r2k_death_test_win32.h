#ifndef R2K_DEATH_TEST_WIN32_H
#define R2K_DEATH_TEST_WIN32_H

#include <r2k_test/r2k_test_suite.h>
#include <r2k_test/r2k_test_runner.h>

void run_death_test_win32(int line_number, const char* executable_path, r2k_test_suite_t* suite);
void fail_death_test_run_win32(r2k_test_runner_t* test_runner);

#endif // R2K_DEATH_TEST_WIN32_H
