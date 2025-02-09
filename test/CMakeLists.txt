macro(deep_test_add filename)
	set(TEST_NAME "deep_${filename}" CACHE INTERNAL "")
	add_executable(${TEST_NAME} ${filename}.c)
	target_link_libraries(${TEST_NAME} PRIVATE deepnova)
	add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endmacro(deep_test_add)

#-----

add_subdirectory(core)

#-----
