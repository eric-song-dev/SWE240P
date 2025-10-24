# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(HashTableAssignment)

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

# Create library target for hash table functionality
add_library(hashtable_lib
    src/HashTable.cpp
    src/AnagramFinder.cpp
    include/HashTable.h
    include/AnagramFinder.h
)
target_include_directories(hashtable_lib PUBLIC include)

# Add the main executable
add_executable(
    hashtable_app
    src/Main.cpp
)
target_link_libraries(hashtable_app PRIVATE hashtable_lib)

# Add test executable
add_executable(
    hashtable_tests
    tests/hashtable_test.cpp
)
target_link_libraries(hashtable_tests
    PRIVATE
    hashtable_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)
if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(hashtable_tests)
else()
    add_test(NAME hashtable_tests COMMAND hashtable_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)