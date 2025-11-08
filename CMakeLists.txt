cmake_minimum_required(VERSION 3.23)

project(lstd)
add_subdirectory(lstd)


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