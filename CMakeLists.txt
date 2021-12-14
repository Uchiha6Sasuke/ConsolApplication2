cmake_minimum_required(VERSION 3.20)
project(hash_tables_AP)
set(CMAKE_CXX_STANDARD 14)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(CMakeTest main.cpp hashtable.h CMakeTest.cpp)
target_link_libraries(CMakeTest gtest_main)
