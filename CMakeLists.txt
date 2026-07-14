cmake_minimum_required(VERSION 3.15)
project(CppDataStructures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

# Main executable
add_executable(datastruct_runner
    main.cpp
)


# GoogleTest
enable_testing()

find_package(GTest REQUIRED)

add_executable(runTests
    test/test_main.cpp
    test/test_dynamicarray/dynamicarray_constructor.cpp
    test/test_dynamicarray/dynamicarray_assignment.cpp
    test/test_dynamicarray/dynamicarray_append.cpp
    test/test_dynamicarray/dynamicarray_remove.cpp
    test/test_dynamicarray/dynamicarray_insert.cpp
    test/test_dynamicarray/dynamicarray_get.cpp
    test/test_dynamicarray/dynamicarray_info.cpp
    test/test_dynamicarray/dynamicarray_clear.cpp
    test/test_dynamicarray/dynamicarray_destructor.cpp
)

target_include_directories(runTests PRIVATE include)

target_link_libraries(runTests
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)