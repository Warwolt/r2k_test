## TODO:

### Assertions
- [x] print args to EXPECT_EQ on failure
  - [x] ~~additionally print integer in ASCII range as char~~
  - [x] write to buffer and make single printf call
  - [x] evaluate `actual` and `expected` only once in assertion
- [x] EXPECT_NEAR for `float` and `double`
- [x] EXPECT_CHAR_EQ for `char`
- [x] EXPECT_STR_EQ for `const char*`
- [ ] let EXPECT_EQ take optional error message string

### Test filtering
- [ ] filter test based on prefix

### Test reporting
- [x] print start and end of test runner
- [x] print start of test suite
- [x] print num passed tests at end of run
- [ ] print num failed tests at end of run

### Test timing
- [ ] print test case duration in ms
- [ ] print suite duration in ms
- [ ] print total duration in ms

### Code base health
- [ ] go through what should be public and what should be internal
- [ ] assert if TEST_SUITE_START not run before running TEST macro
