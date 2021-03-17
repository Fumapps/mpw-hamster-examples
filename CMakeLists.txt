cmake_minimum_required(VERSION 3.17)
project(mpw_hamster_examples)

set(CMAKE_CXX_STANDARD 17)

## Setup Hamstersimulator

include(FetchContent)

FetchContent_Declare(hamster_lib
        GIT_REPOSITORY https://github.com/Fumapps/mpw-modeling-hamster.git
        GIT_TAG cpp-simulator
        SOURCE_DIR hamster_lib
        CMAKE_ARGS "-Wno-dev"
)
FetchContent_GetProperties(hamster_lib)
FetchContent_MakeAvailable(hamster_lib)

set(hamster_ui_SOURCE_DIR ${hamster_lib_SOURCE_DIR}/ui)
get_directory_property(mpw_lib_SOURCE_DIR DIRECTORY ${hamster_lib_SOURCE_DIR} DEFINITION mpw_lib_SOURCE_DIR)
get_directory_property(hamster_ui_SRCS DIRECTORY ${hamster_lib_SOURCE_DIR}/ui DEFINITION SRCS)
string(REGEX REPLACE "([A-Za-z_/]+\\.(h|cpp|c))" "${hamster_ui_SOURCE_DIR}/\\1" hamster_ui_SRCS "${hamster_ui_SRCS}")

include_directories(${mpw_lib_SOURCE_DIR}/core/src/impl)
include_directories(${mpw_lib_SOURCE_DIR}/core/src/generated)
include_directories(${mpw_lib_SOURCE_DIR}/core/src/framework)
include_directories(${hamster_lib_SOURCE_DIR}/core/src/impl)
include_directories(${hamster_lib_SOURCE_DIR}/core/src/generated)
include_directories(${hamster_ui_SOURCE_DIR})

# Own Sources
include_directories(.)
# set(SRCS ${hamster_ui_SRCS})

add_executable(mpw_hamster_examples main.cpp)
target_link_libraries(mpw_hamster_examples hamster_core_lib hamstersimulator_ui_lib)

# Copy resources
add_custom_command(TARGET mpw_hamster_examples PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${hamster_ui_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(TARGET mpw_hamster_examples PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${hamster_lib_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)
