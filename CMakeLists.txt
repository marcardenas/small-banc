cmake_minimum_required(VERSION 3.10)

project(SmallBanc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
FetchContent_MakeAvailable(gtest)

enable_testing()

add_subdirectory(bin)
add_subdirectory(smallbanc)
add_subdirectory(tests)