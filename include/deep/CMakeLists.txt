target_sources(
    deepnova
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/deepinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/deepnova.h
)

#add_subdirectory(event)
add_subdirectory(instance)
