#include <r2k_test/internal/r2k_death_test_win32.h>

#include <r2k_test/internal/r2k_arraylen.h>
#include <r2k_test/internal/r2k_cli_flags.h>

#include <stdio.h>
#include <windows.h>

void run_death_test_win32(int line_number, const char* executable_path, r2k_test_suite_t* suite) {
    SECURITY_ATTRIBUTES sa_attr;
    sa_attr.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa_attr.bInheritHandle = TRUE;
    sa_attr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDERR.
    HANDLE child_stderr_rd = NULL;
    HANDLE child_stderr_wr = NULL;
    if (!CreatePipe(&child_stderr_rd, &child_stderr_wr, &sa_attr, 0)) {
        fprintf(stderr, "R2K Test: Failed to create stderr pipe for death test");
        exit(1);
    }
    // Ensure the read handle to the pipe for STDERR is not inherited.
    if (!SetHandleInformation(child_stderr_rd, HANDLE_FLAG_INHERIT, 0)) {
        fprintf(stderr, "R2K Test: Failed to set stderr handle information for death test");
        exit(1);
    }

    // Create anonymous pipe for communcating death test result
    HANDLE pipe_rd = NULL;
    HANDLE pipe_wr = NULL;
    if (!CreatePipe(&pipe_rd, &pipe_wr, &sa_attr, 0)) {
        fprintf(stderr, "R2K Test: Failed to create anonymous pipe, error = %lu\n", GetLastError());
        exit(1);
    }
    // Ensure the read handle to the anonymous pipe is not inherited.
    if (!SetHandleInformation(pipe_rd, HANDLE_FLAG_INHERIT, 0)) {
        fprintf(stderr, "R2K Test: Failed to set stderr handle information, error = %lu\n", GetLastError());
        exit(1);
    }

    // Create startup information and assign stderr
    STARTUPINFO start_info;
    ZeroMemory(&start_info, sizeof(start_info));
    start_info.cb = sizeof(start_info);
    start_info.hStdError = child_stderr_wr;
    start_info.dwFlags |= STARTF_USESTDHANDLES;

    // Create process information
    PROCESS_INFORMATION process_info;
    ZeroMemory(&process_info, sizeof(process_info));

    // Start the child process.
    char cmd[500] = {0};
    snprintf(cmd, sizeof(cmd)/sizeof(*cmd), "%s %s=%s.%s %s=%d,%lu",
        executable_path,
        // --test_filter=<full suite name>
        TEST_FILTER_FLAG, suite->name, suite->current_test.name,
        // --r2k-test-internal-run-death-test=<line number>,<pipe handle>
        DEATH_TEST_FLAG, line_number, (unsigned long)(size_t)(pipe_wr)
    );
    BOOL process_was_created = CreateProcess(
        NULL,           // Use command line (No module name)
        cmd,            // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        TRUE,           // inherit handles
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &start_info,    // Pointer to STARTUPINFO structure
        &process_info   // Pointer to PROCESS_INFORMATION structure
    );
    if (!process_was_created) {
        fprintf(stderr, "R2K Test: CreateProcess failed for death (%lu).\n", GetLastError());
        exit(1);
    }

    // Wait until child process exits.
    WaitForSingleObject(process_info.hProcess, INFINITE);

    // Close our side of pipes
    CloseHandle(child_stderr_wr);
    CloseHandle(pipe_wr);

    // Write exit code to result
    if (!GetExitCodeProcess(process_info.hProcess, &suite->current_test.death_test_result.exit_code)) {
        if (GetLastError() != ERROR_BROKEN_PIPE) {
            fprintf(stderr, "R2K Test: GetExitCodeProcess failed with code %lu\n", GetLastError());
            exit(1);
        }
    }

    // Write anonymous pipe to `statement_did_not_terminate`
    char pipe_output[2] = {0};
    if (!ReadFile(pipe_rd, pipe_output, arraylen(pipe_output), NULL, NULL)) {
        if (GetLastError() != ERROR_BROKEN_PIPE) {
            fprintf(stderr, "R2K Test: failed to read pipe_wr, error = %lu\n", GetLastError());
            exit(1);
        }
    }
    sscanf(pipe_output, "%d", (int*)&suite->current_test.death_test_result.statement_did_not_terminate);

    // Write child stderr output to result
    ReadFile(child_stderr_rd, suite->current_test.death_test_result.stderr_output, DEATH_TEST_STDERR_LEN, NULL, NULL);

    // Close process and thread handles.
    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
}
