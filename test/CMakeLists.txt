if (NOT TARGET darkstar)
    message(STATUS "Darkstar not found, adding from /external")
    add_subdirectory(${CMAKE_SOURCE_DIR}/external/darkstar)
endif()

macro(deep_test_add filename)
   add_executable(${filename} ${filename}.c)
   target_link_libraries(${filename} PRIVATE deepnova)
   add_test(NAME "deep_${filename}" COMMAND $<TARGET_FILE:${filename}>)
endmacro(deep_test_add)

#-----

add_subdirectory(instance)

#-----
