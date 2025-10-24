# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(BSTAssignment)

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

# Create library target for BST functionality
add_library(bst_lib
    src/BST.cpp
    src/Node.cpp
    include/BST.h
    include/Node.h
    include/Student.h
)
target_include_directories(bst_lib PUBLIC include)

# Add the main executable
add_executable(
    bst_app
    src/Main.cpp
)
target_link_libraries(bst_app PRIVATE bst_lib)

# Add test executable
add_executable(
    bst_tests
    tests/bst_test.cpp
)
target_link_libraries(bst_tests
    PRIVATE
    bst_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)
if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(bst_tests)
else()
    add_test(NAME bst_tests COMMAND bst_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
