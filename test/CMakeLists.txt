macro(deep_test_add filename)
   add_executable(${filename} ${filename}.c)
   target_link_libraries(${filename} PRIVATE deepnova)
   add_test(NAME "deep_${filename}" COMMAND $<TARGET_FILE:${filename}>)
   set_tests_properties("deep_${filename}" PROPERTIES TIMEOUT 30)
endmacro(deep_test_add)

#-----

add_subdirectory(core)

#-----
