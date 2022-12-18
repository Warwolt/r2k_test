# R2K Test

A small test library for C programs, written to closely mimick [Google Test](https://github.com/google/googletest). This is intended as a library that is lightweight and easy to integrate into a C project to add testing capabilities.

R2K Test has the following features:
- Quick compilation time
- Simple to define tests, a test suite is simply a function
- ASSERT_EQ and EXPECT_EQ macros for fatal and non-fatal checks (see [Assertion macros](#assertion-macros))
- Google Test style test reporting with colors
- Disable tests by prefixing them with `DISABLE_`
- Filter tests with `--test-filter=<pattern>`

Want to know more? Check out the [quick tour](./docs/quicktour.md)!

Here's an example unit test file:

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
(todo)

## Assertion macros
The following section will detail the macros that can be used to verify that values hold the expected values inside of `TEST()` blocks.

Some tweaks are made to the assertion macros in comparison to Google Test due to the type system of C; `EXPECT_EQ` only checks integral types, and other primitive types have their own corresponding macros like `EXPECT_EQ_CHAR`, `EXPECT_EQ_PTR`, and `EXPECT_EQ_STR`.

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

**WARNING:** due to the way that `ASSERT_*` macros are implemented, you should **not** call an `ASSERT_*` macro inside of a loop!
