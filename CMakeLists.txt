cmake_minimum_required(VERSION 3.10)

project(SmallBanc CXX)

set(SOURCES bin/smallbanc-cli.cpp)

add_executable(smallbanc-cli ${SOURCES})

include_directories(src)