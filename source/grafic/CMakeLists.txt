target_sources(
    deepnova
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/grafic_module.h
    ${CMAKE_CURRENT_LIST_DIR}/renderer.c
    ${CMAKE_CURRENT_LIST_DIR}/window.c
    ${CMAKE_CURRENT_LIST_DIR}/window_callback.c
    ${CMAKE_CURRENT_LIST_DIR}/window_callback.h
    ${CMAKE_CURRENT_LIST_DIR}/window_helper.c
    ${CMAKE_CURRENT_LIST_DIR}/window_helper.h
)
