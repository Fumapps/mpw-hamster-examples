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

# Race Executable
add_executable(hamster_race race/Race.cpp race/HamsterRaceGame.cpp)
target_include_directories(hamster_race PUBLIC race)

target_link_libraries(hamster_race hamstersimulator_main_lib)

# Copy resources into binary root
add_custom_command(TARGET hamster_race PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/race/ter/ ${CMAKE_CURRENT_BINARY_DIR}/ter)
