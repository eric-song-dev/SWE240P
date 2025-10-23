# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(StackQueueAssignment)

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

# Create library target for stack and queue functionality
add_library(stackqueue_lib
    src/ExpressionEvaluator.cpp
    include/ExpressionEvaluator.h
    include/Queue.h
    include/Stack.h
    include/StackWithTwoQs.h
)
target_include_directories(stackqueue_lib PUBLIC include)

# Add the main executable
add_executable(
    stackqueue_app
    src/Main.cpp
)
target_link_libraries(stackqueue_app PRIVATE stackqueue_lib)

# Add test executable
add_executable(
    stackqueue_tests
    tests/stackqueue_test.cpp
)
target_link_libraries(stackqueue_tests
    PRIVATE
    stackqueue_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)
if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(stackqueue_tests)
else()
    add_test(NAME stackqueue_tests COMMAND stackqueue_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)