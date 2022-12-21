## TODO:

### Assertions
- [x] print args to EXPECT_EQ on failure
  - [x] ~~additionally print integer in ASCII range as char~~
  - [x] write to buffer and make single printf call
  - [x] evaluate `actual` and `expected` only once in assertion
- [x] EXPECT_NEAR for `float` and `double`
- [x] EXPECT_EQ_CHAR for `char`
- [x] EXPECT_EQ_STR for `const char*`
- [ ] let EXPECT_EQ take an optional error message
  - add an EXPECT_EQ_INFO(actual, expected, fmt, ...) macro that EXPECT_EQ wraps?
  - to add a message, you would use the `EXPECT_EQ_INFO` macro, otherwise plain `EXPECT_EQ`
  - `#define EXPECT_EQ(actual, expected) EXPECT_EQ_INFO(actual, expected, "")`
- [ ] EXPECT_EXIT for early termination
  - EXPECT_EXIT(expected_exit_code, statement)
    1. running EXPECT_EXIT() macro sets meta-deta about its position
    2. new process is started with test runner, passing meta-data
    3. the new test runner skips everything until it finds the EXPECT_EXIT with correct tag
    4. this time actually runs the statement in the EXPECT_EXIT argument
    5. terminates process with exit code 0 at end of macro, unless statement already terminated
    6. parent process now resumes, and inspects the exit code
    7. assertion passes if actual exit code matches expected
- [x] ASSERT_* macros corresponding to each EXPECT_*
  - asserting should immediately fail and continue to next test case
  - [ ] Implement ASSERT_* macros in a way that supports loops inside the test
    - currently, calling ASSERT_* inside a loop will break that loop instead of the test
    - although looping inside a test isn't recommended, the current ASSERT_* behavior might be surprising

### Test filtering
- [x] filter test based on prefix
  - [x] exact match
  - [x] wildcard
  - [x] print out that filter is active
- [x] don't run tests prefixex by `DISABLED_`
  - [x] print out num disabled tests

### Test reporting
- [x] print start and end of test runner
- [x] print start of test suite
- [x] print num passed tests at end of run
- [x] print num failed tests at end of run
- [x] print name of failed tests

### Test timing
- [x] print total duration in ms
- [x] print suite duration in ms
- [x] print test case duration in ms

### Advanced testing
- [x] sketch out an idea on how to support parameterized tests (P_TEST)
- [ ] sketch out an idea on how to support property testing (QuickCheck)

### Code base health
- [x] use a CMake for building
- [x] go through what should be public and what should be internal
- [ ] assert that macros and functions called in right order
  - [ ] assert r2k_test_start ran before TEST_SUITE_START
  - [ ] assert TEST_SUITE_START ran before TEST
  - [ ] assert TEST_SUITE_START ran before TEST_SUITE_END
  - [ ] assert TEST_SUITE_END ran before 2nd TEST_SUITE_START
- [x] bugfix the filter prefix matching (it always uses the shorter string as the prefix right now)
- [x] change all includes to use `<>` instead of `""`
