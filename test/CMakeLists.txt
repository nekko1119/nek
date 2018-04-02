include_directories(${CMAKE_SOURCE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTest_INCLUDE_DIRS})

include(files.cmake)

add_executable(nektest ${TEST_SRCS})
target_link_libraries(nektest ${GTEST_LIBRARIES} pthread)

add_test(nektest nektest)
