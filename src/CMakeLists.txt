cmake_minimum_required(VERSION 3.15)

set(TARGET_NAME main)

add_subdirectory(Elevator)
add_subdirectory(Utilities)

add_executable(${TARGET_NAME}
    main.cpp
)

target_link_libraries(${TARGET_NAME}
    PRIVATE 
        Elevator
        Utilities
        cxxopts::cxxopts
        spdlog::spdlog
)

install(
    TARGETS
        ${TARGET_NAME}
    DESTINATION
        "${CMAKE_INSTALL_BIN_DIR}"
)