cmake_minimum_required(VERSION 3.20)
project(Phantom)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
add_executable(${PROJECT_NAME} ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src/)

# Set the folder where the executable will be created
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Librairies

# ---Add glbasimac---
add_subdirectory(lib/glbasimac)
target_link_libraries(${PROJECT_NAME} PRIVATE glbasimac)

include(CmakeUtils/files_and_folders.cmake)
Cool__target_copy_folder(${PROJECT_NAME} "assets")


# ---simpleText--- (fork from https://github.com/podgorskiy/SimpleText)
# Optional library for rendering text
include(FetchContent)
FetchContent_Declare(
    simpletext
    GIT_REPOSITORY https://github.com/dsmtE/SimpleText/
)

FetchContent_MakeAvailable(simpletext)

# Create an interface library for simpletext
add_library(simpletext INTERFACE)
target_include_directories(simpletext SYSTEM INTERFACE ${simpletext_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE simpletext)