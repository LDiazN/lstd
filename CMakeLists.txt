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

    PRIVATE 
    lstd/collections/vector.cpp
    lstd/memory/rc_ptr.cpp
)


# -- < Testing > ----------------------
option(BUILD_TESTS "If should build tests" OFF)

if (BUILD_TESTS)
add_subdirectory(dependencies/Catch2)
add_executable(tests)
target_sources(tests
    PRIVATE 
    tests/vector.cpp
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