## TODO:

### Assertions
- [x] print args to EXPECT_EQ on failure
  - [x] ~~additionally print integer in ASCII range as char~~
  - [x] write to buffer and make single printf call
  - [x] evaluate `actual` and `expected` only once in assertion
- [x] EXPECT_NEAR for `float` and `double`
- [x] EXPECT_CHAR_EQ for `char`
- [x] EXPECT_STR_EQ for `const char*`
- [ ] let EXPECT_EQ take an optional error message string
- [ ] EXPECT_ASSERT for checking `assert` calls (early termination)

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

### Code base health
- [ ] use a CMake for building
- [ ] go through what should be public and what should be internal
- [ ] assert that macros and functions called in right order
  - [ ] assert r2k_test_start ran before TEST_SUITE_START
  - [ ] assert TEST_SUITE_START ran before TEST
  - [ ] assert TEST_SUITE_START ran before TEST_SUITE_END
  - [ ] assert TEST_SUITE_END ran before 2nd TEST_SUITE_START
- [ ] bugfix the filter prefix matching (it always uses the shorter string as the prefix right now)
