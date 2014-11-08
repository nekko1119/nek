cmake_minimum_required(VERSION 2.8)
project(nek)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")

if(CMAKE_COMPILER_IS_GNUCXX)
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GXX_VERSION)
  if (GXX_VERSION VERSION_LESS 4.8)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
  else()
    set (CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
  endif()
endif()

enable_testing()
add_subdirectory(test)
