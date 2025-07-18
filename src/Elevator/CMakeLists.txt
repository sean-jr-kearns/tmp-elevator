cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME Elevator)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${TARGET_NAME} ${SRC})

target_include_directories(${TARGET_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${TARGET_NAME}
    PUBLIC 
        spdlog::spdlog
)

install(
    TARGETS
        ${TARGET_NAME}
    EXPORT ElevatorTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    FILES Elevator.hpp 
    DESTINATION include
)
