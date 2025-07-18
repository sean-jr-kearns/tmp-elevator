cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
add_compile_options(-Wall -Wextra -pedantic)

set(TARGET_NAME main)

project(${TARGET_NAME})

# Get external dependencies
include(FetchContent)
# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(spdlog)

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Add libraries
#file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#add_library(${TARGET_NAME} SHARED ${SRC})

# Add subdirectories 
add_subdirectory(src)
add_subdirectory(tests)

target_compile_options(${TARGET_NAME} PRIVATE -Werror)