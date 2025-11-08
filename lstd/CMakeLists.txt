add_library(lstd INTERFACE)

add_subdirectory(vector)

target_link_libraries(lstd 
    INTERFACE 
        vector
)

target_include_directories(lstd
    INTERFACE
        vector
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # points to src/
)