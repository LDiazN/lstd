add_library(vector)
target_sources(vector
    PRIVATE vector.cpp
    PUBLIC
    FILE_SET HEADERS
    FILES 
        vector.hpp
)

# Set the include directory so it appears as <lstd/vector.hpp>
target_include_directories(vector
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>  # points to src/
        $<INSTALL_INTERFACE:include>                       # for install
)