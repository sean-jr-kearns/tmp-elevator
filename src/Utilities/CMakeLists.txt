cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME Utilities)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_library(${TARGET_NAME} 
    INTERFACE
        ${SRC}
)

target_include_directories(${TARGET_NAME} 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME}
    INTERFACE 
        spdlog::spdlog
)

install(
    FILES 
        Utilities.hpp 
    DESTINATION include
)
