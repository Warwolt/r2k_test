cmake_minimum_required(VERSION 3.16.0)
project(r2ktest)
enable_language(C)

option(r2ktest_build_tests "Build unit tests for r2k_test" OFF)
option(r2ktest_build_samples "Build r2k_test sample files" OFF)

set(SRC
    src/r2k_string_util.c
    src/r2k_test_assert.c
    src/r2k_test_runner.c
    src/r2k_test_suite.c
    src/r2k_test.c
    src/r2k_timer.c
)

#
# R2K Test library
#
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    ${SRC}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# R2K Test sample files
#
if(r2ktest_build_samples)
    add_executable(sample1_basic_usage
        samples/sample1_basic_usage.c
        ${SRC}
    )

    target_include_directories(sample1_basic_usage PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif(r2ktest_build_samples)

#
# Internal unit tests
#
if(r2ktest_build_tests)
    add_executable(unit_tests
        test/main.c
        ${SRC}
    )

    target_include_directories(unit_tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endif(r2ktest_build_tests)

