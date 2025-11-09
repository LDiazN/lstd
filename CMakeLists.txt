cmake_minimum_required(VERSION 3.23)

project(lstd)
add_library(lstd)

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
add_subdirectory(lib/Catch2)
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