cmake_minimum_required(VERSION 3.0)
project(solver)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Werror")

include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cc src/*.h)

find_package(Boost COMPONENTS program_options)

add_executable(solver src/main.cc ${LIBS} ${SOURCES})

target_link_libraries(solver ${Boost_LIBRARIES})

find_program(VALGRIND valgrind)
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --leak-check=full $<TARGET_FILE:solver>)
endif()
