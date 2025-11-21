cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(MIPS_MODEL VERSION 1.0)

if(MIPS_SC_EXE)
    find_package(SystemCLanguage REQUIRED)
    find_package(SystemC REQUIRED)

    # Help CMake find SystemC by using the SYSTEMC_HOME environment variable
    if(DEFINED ENV{SYSTEMC_HOME})
        list(APPEND CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})
    endif()
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Setting max display logger level: lerror, lwarning,linfo, ldebug, ldebug1-4
#set(FILELOG_MAX_LEVEL "ldebug4") # Display every debug message
set(FILELOG_MAX_LEVEL "linfo") # Only Display essential message

# Generate the static library from the library sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

configure_file(${PROJECT_SOURCE_DIR}/include/mips_sim/build_info.h.in
               ${PROJECT_SOURCE_DIR}/include/mips_sim/build_info.h)
message("--- Add mips_sim library")
add_library(mips_sim STATIC
    ${SOURCES}
)

target_include_directories(mips_sim
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/projects
)

############################################################
# Create an executable
############################################################
if(MIPS_EXE)
    message("--- Add mips_sim execute")
    set(EXE_SOURCES
        ${PROJECT_SOURCE_DIR}/projects/mips_sim/main.cpp
    )

    set(IN_DATA_PATH "\"${PROJECT_SOURCE_DIR}/data/in\"")

    configure_file(${PROJECT_SOURCE_DIR}/projects/mips_sim/data_path.h.in
                ${PROJECT_SOURCE_DIR}/projects/mips_sim/data_path.h)
    # Add an executable with the above sources
    add_executable(mips_simulate
        ${EXE_SOURCES}
    )

    target_include_directories(mips_simulate
        PUBLIC
        ${PROJECT_SOURCE_DIR}/thirdparty
        ${PROJECT_SOURCE_DIR}/projects/mips_sim
    )

    # link the new mips_sim target with the mips_ut target
    target_link_libraries(mips_simulate
        PRIVATE
        mips_sim
    )
endif()

############################################################
# Create a SystemC executable
############################################################
if(MIPS_SC_EXE)
    message("--- Add mips_sim_sc execute")
    set(EXE_SC_SOURCES
        ${PROJECT_SOURCE_DIR}/projects/mips_sim/main_sc.cpp
    )

    # Add an executable with the above sources
    add_executable(mips_sc_sim
        ${EXE_SC_SOURCES}
    )

    target_include_directories(mips_sc_sim
        PUBLIC
        ${PROJECT_SOURCE_DIR}/thirdparty
        ${PROJECT_SOURCE_DIR}/projects/mips_sim
    )

    # link the new mips_sim target with the mips_ut target
    target_link_libraries(mips_sc_sim
        PRIVATE
        mips_sim
        SystemC::systemc
    )
endif()

############################################################
# Create an unit test
############################################################

if(UNIT_TEST)
    message("--- Add mips_sim unit test")
    file(GLOB_RECURSE TEST_SOURCES "./projects/unit_test/*.cpp")

    set(IN_DATA_PATH "\"${PROJECT_SOURCE_DIR}/data/in\"")
    set(OUT_DATA_PATH "\"${PROJECT_SOURCE_DIR}/data/out\"")
    set(LOGGER_PATH "\"${PROJECT_SOURCE_DIR}/data/log\"")
    configure_file(${PROJECT_SOURCE_DIR}/projects/unit_test/data_path.h.in
                ${PROJECT_SOURCE_DIR}/projects/unit_test/data_path.h)

    # Add an executable with the above sources
    add_executable(mips_ut
        ${TEST_SOURCES}
    )

    target_include_directories(mips_ut
        PUBLIC
        ${PROJECT_SOURCE_DIR}/thirdparty
        ${PROJECT_SOURCE_DIR}/projects
    )

    # link the new mips_sim target with the mips_ut target
    target_link_libraries(mips_ut
        PRIVATE
        mips_sim
    )
endif()