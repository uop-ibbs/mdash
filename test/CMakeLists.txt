if (BUILD_AMBER)
    set(MAKE_CHECK_COMMAND ${PROJECT_SOURCE_DIR}/test/test.sh -mdash ../src/dash/mdash -inputs ${PROJECT_SOURCE_DIR}/examples -expected ${PROJECT_SOURCE_DIR}/test -amber)
else()
    set(MAKE_CHECK_COMMAND ${PROJECT_SOURCE_DIR}/test/test.sh -mdash ../src/dash/mdash -inputs ${PROJECT_SOURCE_DIR}/examples -expected ${PROJECT_SOURCE_DIR}/test)
endif()

add_custom_target(check COMMAND ${MAKE_CHECK_COMMAND})
