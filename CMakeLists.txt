cmake_minimum_required(VERSION 2.8)
project(nek)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

add_executable(nektest "./test/main.cpp")
target_link_libraries(nektest ${GTEST_LIBRARIES} pthread)
add_test(nektest nektest)
