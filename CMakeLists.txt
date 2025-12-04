cmake_minimum_required(VERSION 3.23)

project(lstd)
add_library(lstd)

# To add a new file, add its header in the public "FILES" section
# and cpp files in the PRIVATE section
target_sources(lstd
    PUBLIC
    FILE_SET HEADERS
    FILES
        lstd/collections/vector.hpp
        lstd/memory/rc_ptr.hpp
        lstd/memory/box_ptr.hpp
        lstd/debug/assert.hpp
        lstd/utils/pair.hpp

    PRIVATE
    lstd/collections/vector.cpp
    lstd/memory/rc_ptr.cpp
    lstd/debug/assert.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(lstd PRIVATE DEBUG)
endif()

# -- < Testing > ----------------------
option(BUILD_TESTS "If should build tests" OFF)

if (BUILD_TESTS)
target_compile_definitions(lstd PRIVATE DEBUG)

add_subdirectory(dependencies/Catch2)
add_executable(tests)
target_sources(tests
    PRIVATE
    tests/vector.cpp
    tests/rc_ptr.cpp
    tests/box_ptr.cpp
    tests/pair.cpp
)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        lstd
)
include(CTest)
include(Catch)
catch_discover_tests(tests)
endif()