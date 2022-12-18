# R2K Test

A small test library for C programs, written to closely mimick [Google Test](https://github.com/google/googletest). This is intended as a library that is lightweight and easy to integrate into a C project to add testing capabilities.

Some tweaks are made to the assertion macros in comparison to Google Test due to the type system of C; `EXPECT_EQ` only checks integral types, and other primitive types have their own corresponding macros like `EXPECT_EQ_CHAR`, `EXPECT_EQ_PTR`, and `EXPECT_EQ_STR`.

## Quick tour

Tests in R2K Test are defined with a `TEST()` macro, and the tests are defined inside of a function that becomes the test suite for those tests. These test suites are then ran by calling the corresponding functions from a test runner program.

The test runner program should start with a call to `r2k_test_start()` and end with returning the value of `r2k_test_end`. Calls to all test suites happen in between these two functions.

### Defining a test suite
Here's an example test runner program with a test suite `arithmetic_tests`:

```C
#include <r2k_test/r2k_test.h>

void arithmetic_tests() {
    TEST_SUITE_START();

    TEST(addition_is_commutative) {
        EXPECT_EQ(2 + 3, 3 + 2);
    }

    TEST(zero_is_additive_identity) {
        EXPECT_EQ(2 + 0, 2);
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    arithmetic_tests();

    return r2k_test_end();
}
```

Running this on the command line gives an output that is very familiar to someone who's used Google Test:

![arithmetic_tests_example](docs/arithmetic_tests.png)

Note that the function name `void arithmetic_tests()` gives the name of the test suite, as seen in e.g. the `arithmetic_tests.addition_is_commutative` output.

### Asserting in tests

We can tweak one of the tests so that it contains an error:

```C++
TEST(zero_is_additive_identity) {
    EXPECT_EQ(2 + 1, 2);
}
```

Running this prints out an error message with details like in Google Test:

![arithmetic_tests_failed_example](docs/arithmetic_tests_failed.png)

### Disabling tests

Like in Google Test, a test case can be disabled by prefixing its name with `DISABLED_`:

```C++
TEST(DISABLED_addition_is_commutative) {
    EXPECT_EQ(2 + 3, 3 + 2);
}
```

This will behave in the same way as in Google Test when running the tests, where that case is now omitted, and a reminder text is printed at the end of the output that there are disabled tests:

![arithmetic_tests_disabled_example](docs/arithmetic_tests_disabled.png)

### Filtering tests

By passing a `--test_filter=<pattern>` argument to the test runner program, only the test cases that fit the pattern will be ran. The `<pattern>` is a string that will be matched against the full name of the test case, where the full name is e.g. `arithmetic_tests.addition_is_commutative`. The pattern can contain a `*` wildcard, that makes the filter only prefix match.

Here's an example of running the test program with the `--test_filter=arithmetic_tests.addition*` argument:

![arithmetic_tests_filtered_example](docs/arithmetic_tests_filtered.png)

## Build instructions
R2K Test is a CMake based project. The recommended way to integrate R2K Test into your project is to first clone it as submodule, and then add it as a dependency to your top-level `CMakeLists.txt` file.

To add it as a submodule, from the root of your project run:

```bash
mkdir external
cd external
git submodule add https://github.com/Warwolt/r2k_test.git
```

Then, in your top-level `CMakeLists.txt` file, add:

```
add_subdirectory(external/r2k_test)
```

and:

```
target_link_libraries(<your-test-runner> PRIVATE my_lib)
```

where `<your-test-runner>` is the executable that will run the tests. For example test runners, see the `sample` directory.

### Building the samples and unit tests
This project is bundled with its own internal unit tests, and some sample test runners. In order to build them, first navigate into the root of this project from your command line. Then run:

```bash
cmake -B build -Dr2ktest_build_tests=ON -Dr2ktest_build_samples=ON .
cmake --build build
```

To run the built executables, run the following:

```bash
./build/unit_tests
```

or

```bash
./build/sample1_basic_usage
```

## Assertion macros
(todo)
