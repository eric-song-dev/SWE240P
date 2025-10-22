# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(BankAssignment)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent for downloading Google Test
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Create library target for bank functionality
add_library(bank_lib
    src/Bank.cpp
    include/Bank.h
)
target_include_directories(bank_lib PUBLIC include)

# Add the main executable
add_executable(
    bank_app
    src/Main.cpp
)
target_link_libraries(bank_app PRIVATE bank_lib)

# Add test executable
add_executable(
    bank_tests
    tests/bank_test.cpp
)
target_link_libraries(bank_tests
    PRIVATE
    bank_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
# Control whether to run test discovery at build time.
# Some Xcode configurations run the test executable in a post-build script
# (via gtest_discover_tests) which can cause the build to fail if the test
# binary crashes or is killed. Provide an option to disable discovery during
# the build and instead register the test with CTest so you can run it
# manually via `ctest` or Xcode's test runner.
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)

if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(bank_tests)
else()
    # Register the test without executing the test binary during the build.
    add_test(NAME bank_tests COMMAND bank_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
