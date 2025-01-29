cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(deepnova LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(deepnova)

target_link_libraries(
    deepnova
    PUBLIC
    darkstar
    glfw
)

set(DEEP_VERSION_MAJOR 0 CACHE INTERNAL "")
set(DEEP_VERSION_MINOR 1 CACHE INTERNAL "")
set(DEEP_VERSION_PATCH 0 CACHE INTERNAL "")
set(DEEP_VERSION_TWEAK 0 CACHE INTERNAL "")

target_compile_definitions(
    deepnova
    PUBLIC
    ___DEEP_VERSION_MAJOR=${DEEP_VERSION_MAJOR}
    ___DEEP_VERSION_MINOR=${DEEP_VERSION_MINOR}
    ___DEEP_VERSION_STAGE=${DEEP_VERSION_PATCH}
    ___DEEP_VERSION_PATCH=${DEEP_VERSION_TWEAK}
)

if(DEEP_TEST_ENABLE)
	enable_testing()
	add_subdirectory(test)
endif()

add_subdirectory(include)
add_subdirectory(library)
add_subdirectory(source)
