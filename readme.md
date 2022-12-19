# R2K Test

A small test library for C programs, written to closely mimick [Google Test](https://github.com/google/googletest). This is intended as a library that is lightweight and easy to integrate into a C project to add testing capabilities.

R2K Test has the following features:
- Quick compilation time
- ISO C99 compliant
- Simple to define tests; test suites are functions, and test cases are block statements within those functions
- ASSERT_EQ and EXPECT_EQ macros for fatal and non-fatal checks (see [Assertion macros](#assertion-macros))
- Google Test style test reporting with colors
- Disable tests by prefixing them with `DISABLE_`
- Filter tests with `--test-filter=<pattern>`
- Parameterized tests

Want to know more? Check out the [quick tour](./docs/quicktour.md)!

Here's an example unit test file:

```C
#include <r2k_test/r2k_test.h>

void arithmetic_tests(void) {
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
target_link_libraries(<your-test-runner> PRIVATE r2k_test)
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

## Writing tests
Since C is a procedural programming language, R2K Test is procedural as well. Unlike Google Test, where tests can auto-register themselves, in R2K Test a test is run if someone calls it. To make it easy to add tests, the following principles are used:

- A test suite is a function
- A test case is a block statement inside of a test suite function

Every test case will run one after the other inside of the test suite as soon as the suite is called, and all test suites are called from a `main` function in a test runner program.

The test runner program `main` will look like this:

```C
#include <r2k_test/r2k_test.h>

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    // test suites called here

    return r2k_test_end();
}
```

To add a test suite to this test runner, all we need to do is add a function and call it. A function becomes a test suite by the function including the `TEST_SUITE_START()` and `TEST_SUITE_END()` macros:

```C
#include <r2k_test/r2k_test.h>

void hello_world_tests(void) {
    TEST_SUITE_START();

    // test cases go here

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    hello_world_tests();

    return r2k_test_end();
}
```

The name of the test suite will be the same as the function, so in this case the test suite we added will be called `hello_world`. To add test cases to the `hello_world` test suite, we add a `{}` block prefixed with the `TEST()` macro, which is passed the name of the test case.

```C
#include <r2k_test/r2k_test.h>

void hello_world_tests(void) {
    TEST_SUITE_START();

    TEST(hello_world) {
        EXPECT_EQ(1 + 1, 2);
    }

    TEST_SUITE_END();
}

int main(int argc, char** argv) {
    r2k_test_start(argc, argv);

    hello_world_tests();

    return r2k_test_end();
}
```

When you run this test runner, the full name of the test we added will be `hello_world_tests.hello_world`. For a complete example of a test runner, see the [basic usage](samples/sample1_basic_usage.c) sample file.

## Parameterized tests
R2K Test supports a simplified version of parameterized tests, that are defined with the `TEST_P` macro. A parameterized test will be ran once for each value in its parameter list, which means that the test can check that its assertions hold for all of those values.

The parameterized test macro `TEST_P(test_name, parameter_type, parameters)` takes the name of the test, the type of the parameter and then a comma separated list of values to run the test for.

Inside of the test, the current test parameter is accessed with the `get_param()` macro.

The tests in the arithmetic test suite makes statement about "all numbers". Although we can't reasonably check every number, we can still test that the assertions hold for more than one case by using a `P_TEST`:

```C
typedef struct int_pair {
    int x;
    int y;
} int_pair_t;

void arithmetic_tests(void) {
    TEST_SUITE_START();

    P_TEST(addition_is_commutative, int_pair_t, {1,2}, {2,3}, {3,4}) {
        int x = get_param().x;
        int y = get_param().y;
        EXPECT_EQ(x + y, y + x);
    }

    P_TEST(zero_is_additive_identity, int, 1, 2, 3) {
        int num = get_param();
        EXPECT_EQ(num + 0, num);
    }

    TEST_SUITE_END();
}
```

When running the `arithmetic_tests` suite, it will now run 6 tests instead of just 2, since we have supplied 3 values each to both tests in the suite.

**Note:** Unlike Google Test, R2K Test does no support printing out the value of the current test parameter upon failure, since C lacks the ability to stringify an arbitray run-time value.

## Assertion macros
The following section will detail the macros that can be used to verify that values hold the expected values inside of `TEST()` blocks.

Some tweaks are made to the assertion macros in comparison to Google Test due to the type system of C; `EXPECT_EQ` only checks integral types, and other primitive types have their own corresponding macros like `EXPECT_EQ_CHAR`, `EXPECT_EQ_PTR`, and `EXPECT_EQ_STR`.

Using the correct assertion macro will make sure that the best kind of error details can be provided if the assertion fails. For example, `EXPECT_EQ_CHAR` will print the actual character instead of the numeric value of the characters passed to it.

**WARNING:** due to the way that `ASSERT_*` macros are implemented, you should **not** call an `ASSERT_*` macro inside of a loop! If you need assert over a range of values, consider to instead use a [parameterized test](#parameterized-tests).

| Macro name                                      | Type        | Assertion                                    |
| ----------------------------------------------- | ----------- | -------------------------------------------- |
| EXPECT_TRUE(actual)                             | booelan     | `actual` equals `true`                       |
| EXPECT_FALSE(actual)                            | booelan     | `actual` equals `false`                      |
| EXPECT_EQ(actual, expected)                     | integer     | `actual` is the same integer as `expected`   |
| EXPECT_EQ_CHAR(actual, expected)                | character   | `actual` is the same character as `expected` |
| EXPECT_EQ_PTR(actual, expected)                 | pointer     | `actual` is the same pointer as `expected`   |
| EXPECT_EQ_STR(actual, expected)                 | const char* | `actual` is the same string as `expected`    |
| EXPECT_NEAR_FLOAT(actual, expected, abs_error)  | float       | `actual` is within `abs_error` of `expected` |
| EXPECT_NEAR_DOUBLE(actual, expected, abs_error) | double      | `actual` is within `abs_error` of `expected` |

Every `EXPECT_*` macro has a corresponding `ASSERT_*` macro. A test will continue running if an `EXPECT_*` macro fails, but will stop if an `ASSERT_*` macro fails.


