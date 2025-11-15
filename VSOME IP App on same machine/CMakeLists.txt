cmake_minimum_required(VERSION 3.10)
project(vsomeip_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Try to find vSomeIP headers & libs (adjust PATHS if installed elsewhere)
find_path(VSOMEIP_INCLUDE_DIR
    NAMES vsomeip/vsomeip.hpp
    PATHS /usr/include /usr/local/include /opt/include
)

find_library(VSOMEIP_LIB
    NAMES vsomeip3
    PATHS /usr/lib /usr/local/lib /opt/lib
)

find_library(VSOMEIP_CFG_LIB
    NAMES vsomeip3-cfg
    PATHS /usr/lib /usr/local/lib /opt/lib
)

if(NOT VSOMEIP_INCLUDE_DIR)
    message(FATAL_ERROR "vsomeip headers not found! (set VSOMEIP_INCLUDE_DIR or install headers)")
endif()

if(NOT VSOMEIP_LIB OR NOT VSOMEIP_CFG_LIB)
    message(FATAL_ERROR "vsomeip libraries not found! (set VSOMEIP_LIB or install libs)")
endif()

include_directories(
    include
    ${VSOMEIP_INCLUDE_DIR}
)

add_executable(server src/server.cpp)
target_link_libraries(server ${VSOMEIP_LIB} ${VSOMEIP_CFG_LIB})

add_executable(client src/client.cpp)
target_link_libraries(client ${VSOMEIP_LIB} ${VSOMEIP_CFG_LIB})
