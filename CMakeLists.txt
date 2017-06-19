cmake_minimum_required(VERSION 3.0)
project(solver)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Werror")

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cc src/*.h)
file(GLOB_RECURSE TESTS tests/*.cc)

find_package(Boost COMPONENTS program_options)

add_executable(solver src/main.cc ${SOURCES})
target_link_libraries(solver ${Boost_LIBRARIES})

find_program(VALGRIND valgrind)
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --leak-check=full $<TARGET_FILE:solver>)
endif()

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE include/catch)

add_executable(solver-test tests/test_main.cc ${TESTS})
target_link_libraries(solver-test Catch ${Boost_LIBRARIES})

enable_testing()
add_test(NAME tests COMMAND solver-test)
