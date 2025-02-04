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

###########
# VERSION #
###########

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

#######################
# CONFIGURATION TYPE #
#######################

set_target_properties(deepnova PROPERTIES
    CMAKE_CXX_FLAGS_RELWITHDEBUG "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DDEBUG"
    CMAKE_C_FLAGS_RELWITHDEBUG "${CMAKE_C_FLAGS_RELWITHDEBINFO} -DDEBUG"
    CMAKE_EXE_LINKER_FLAGS_RELWITHDEBUG "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}"
    CMAKE_CXX_FLAGS_RELTEST "${CMAKE_CXX_FLAGS_RELEASE}"
    CMAKE_C_FLAGS_RELTEST "${CMAKE_C_FLAGS_RELEASE}"
    CMAKE_EXE_LINKER_FLAGS_RELTEST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}"
)

foreach(CONFIG RelWithDebug RelTest)
    target_compile_definitions(deepnova PRIVATE $<$<CONFIG:${CONFIG}>:${CMAKE_C_FLAGS_${CONFIG}}>)
    target_link_options(deepnova PRIVATE $<$<CONFIG:${CONFIG}>:${CMAKE_EXE_LINKER_FLAGS_${CONFIG}}>)
endforeach()

################
# GLFW OPTIONS #
################

set(BUILD_SHARED_LIBS FALSE CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES FALSE CACHE INTERNAL "")
set(GLFW_BUILD_TESTS FALSE CACHE INTERNAL "")
set(GLFW_BUILD_DOCS FALSE CACHE INTERNAL "")
set(GLFW_VULKAN_STATIC FALSE CACHE INTERNAL "")

############
# TESTING #
############

if(DEEP_TEST_ENABLE)
	enable_testing()
	add_subdirectory(test)
endif()

################
# SUBDIRECTORY #
################

add_subdirectory(include)
add_subdirectory(library)
add_subdirectory(source)
