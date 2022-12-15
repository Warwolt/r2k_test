## TODO:

- [x] print start and end of test runner
- [x] print start of test suite
- [x] 1 suite with 1 case
- [x] 1 passing test
- [x] 1 failing test with EXPECT_EQ
- [x] print args to EXPECT_EQ on failure
  - [ ] additionally print integer in ASCII range as char
  - [x] write to buffer and make single printf call
  - [x] evaluate `actual` and `expected` only once in assertion
  - [ ] EXPECT_NEAR for `float` and `double`
  - [ ] EXPECT_STR_EQ for `const char*`
- [ ] print num failed tests at end
- [ ] let EXPECT_EQ take optional error message string
