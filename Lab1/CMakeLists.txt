cmake_minimum_required(VERSION 3.15)
project(list)

set(CMAKE_CXX_STANDARD 17)
set(GOOGLETEST_VERSION 777)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests listGoogleTests.cpp)
target_link_libraries(tests gtest gtest_main)