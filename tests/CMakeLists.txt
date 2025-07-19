cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME test_elevator)

file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/Elevator/*.cpp")

add_executable(${TARGET_NAME} ${SRC})

target_link_libraries(${TARGET_NAME}
    PRIVATE 
        Elevator
        GTest::gtest_main
        spdlog::spdlog
)

include(GoogleTest)

gtest_discover_tests(${TARGET_NAME})