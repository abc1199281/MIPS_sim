cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(MIPS_MODEL VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MIPS_MODEL ./common/main.cpp)

target_include_directories(MIPS_MODEL PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )