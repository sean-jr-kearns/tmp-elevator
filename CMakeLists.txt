cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
add_compile_options(-Wall -Wextra -pedantic)

set(TARGET_NAME main)

project(${TARGET_NAME})

find_package(cxxopts REQUIRED)
find_package(spdlog REQUIRED)

# Add subdirectories 
add_subdirectory(src)

# Only build tests if enabled
if(WITH_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(tests)
endif()

target_compile_options(${TARGET_NAME} PRIVATE -Werror)