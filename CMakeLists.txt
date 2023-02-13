cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(MIPS_MODEL VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate the static library from the library sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
message(SOURCES="${SOURCES}")

add_library(mips_sim STATIC    
    ${SOURCES}
)

target_include_directories(mips_sim
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

file(GLOB_RECURSE TEST_SOURCES "./projects/unit_test/*.cpp")

message(TEST_SOURCES="${TEST_SOURCES}")

# Add an executable with the above sources
add_executable(mips_ut
    ${TEST_SOURCES}
    #${PROJECT_SOURCE_DIR}/include
)

target_include_directories(mips_ut
    PUBLIC
    ${PROJECT_SOURCE_DIR}/thirdparty
)

# link the new mips_sim target with the mips_ut target
target_link_libraries(mips_ut
    PRIVATE 
    mips_sim
)