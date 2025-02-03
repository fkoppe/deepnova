cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(deepnova LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(deepnova)

set(DEEPNOVA_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

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

set(BUILD_SHARED_LIBS FALSE CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES FALSE CACHE INTERNAL "")
set(GLFW_BUILD_TESTS FALSE CACHE INTERNAL "")
set(GLFW_BUILD_DOCS FALSE CACHE INTERNAL "")
set(GLFW_VULKAN_STATIC FALSE CACHE INTERNAL "")

if(DEEP_TEST_ENABLE)
	enable_testing()
	add_subdirectory(test)
endif()

if(DEEP_WORKFLOW)
	target_include_directories(deepnova ${DARKSTAR_WORKFLOW_DIR}/include)
	target_link_directories(deepnova ${DARKSTAR_WORKFLOW_DIR}/lib)
endif()

add_subdirectory(include)
add_subdirectory(library)
add_subdirectory(source)
