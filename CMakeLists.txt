cmake_minimum_required(VERSION 3.23)

project(lstd)
add_subdirectory(lstd/vector)

add_library(lstd INTERFACE )
target_link_libraries(lstd INTERFACE vector)


# -- < Testing > ----------------------
add_subdirectory(lib/Catch2)
add_executable(tests tests/tests.cpp)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        lstd
)
include(CTest)
include(Catch)
catch_discover_tests(tests)