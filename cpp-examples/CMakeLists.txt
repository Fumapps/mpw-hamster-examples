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
if(NOT hamster_lib_POPULATED)
    FetchContent_Populate(hamster_lib)
    add_subdirectory(${hamster_lib_SOURCE_DIR} ${hamster_lib_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Race Executable
set(SRCS race/Main.cpp
        race/HamsterRaceGame.h race/HamsterRaceGame.cpp
        race/RaceHamster.h race/RaceHamster.cpp)

add_executable(hamster_race ${SRCS})
target_include_directories(hamster_race PUBLIC race)

target_link_libraries(hamster_race hamstersimulator_main_lib)

# Copy resources into binary root
add_custom_command(TARGET hamster_race PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/race/ter/ ${CMAKE_CURRENT_BINARY_DIR}/ter)

# Windows: Copy SDL DLLs into output directory
if (MSVC)
    include(${CMAKE_SOURCE_DIR}/CMakeListsLocalProperties.cmake) # define SDL properties on Windows
    # copy SDL DLLs to output
    add_custom_command(TARGET hamster_race POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${SDL2_DIR}/lib/x64/ ${CMAKE_CURRENT_BINARY_DIR})
    # copy SDL_image DLLs to output
    add_custom_command(TARGET hamster_race POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${SDL2_IMAGE_DIR}/lib/x64/ ${CMAKE_CURRENT_BINARY_DIR})
    # copy SDL_ttf DLLs to output
    add_custom_command(TARGET hamster_race POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${SDL2_TTF_DIR}/lib/x64/ ${CMAKE_CURRENT_BINARY_DIR})
endif ()
