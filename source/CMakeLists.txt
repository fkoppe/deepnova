target_sources(
    deepnova
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/deep_library.h
)

target_precompile_headers(
    deepnova
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/deep_library.h
)

add_subdirectory(surface)
