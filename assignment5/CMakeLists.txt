# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(HeapAssignment)

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

# Create library target for heap functionality
add_library(heap_lib
    src/HeapBuilder.cpp
    src/BSTToHeapTransformer.cpp
    src/IntBST.cpp
    include/HeapBuilder.h
    include/BSTToHeapTransformer.h
    include/IntBST.h
    include/Node.h
)
target_include_directories(heap_lib PUBLIC include)

# Add the main executable
add_executable(
    heap_app
    src/Main.cpp
)
target_link_libraries(heap_app PRIVATE heap_lib)

# Add test executable
add_executable(
    heap_tests
    tests/heap_test.cpp
)
target_link_libraries(heap_tests
    PRIVATE
    heap_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)
if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(heap_tests)
else()
    add_test(NAME heap_tests COMMAND heap_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
