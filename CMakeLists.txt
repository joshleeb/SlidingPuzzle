cmake_minimum_required(VERSION 3.0)
project(solver)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Werror")

include_directories(include)

##############################################################################
# Main
##############################################################################

# Find main sources in `src` directory.
file(GLOB_RECURSE SOURCES src/*.cc src/*.h)

# Add library for the source files.
add_library(src ${SOURCES})

# Load Boost libraries.
find_package(Boost COMPONENTS program_options)

# Create executable and link libraries.
add_executable(solver src/main.cc)
target_link_libraries(solver src ${Boost_LIBRARIES})

##############################################################################
# Valgrind
##############################################################################

# Find `valgrind` and create a make target for checking memory leaks if found.
find_program(VALGRIND valgrind)
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --leak-check=full $<TARGET_FILE:solver>)
endif()

##############################################################################
# Testing
##############################################################################

# Find test files in `tests` directory.
file(GLOB_RECURSE TESTS tests/*.cc)

# Add libraries for source files and the catch header.
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE include/catch)

# Create executable for testing and link libraries.
add_executable(test-solver tests/test_main.cc ${TESTS})
target_link_libraries(test-solver Catch src)

# Enable testing and add test command.
enable_testing()
add_test(NAME tests COMMAND test-solver)
