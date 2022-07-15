add_executable(testbed main.cpp)
target_link_libraries(testbed PRIVATE engine)
target_include_directories(testbed
        PRIVATE ${CMAKE_SOURCE_DIR}/src/engine )

add_custom_command(TARGET testbed POST_BUILD        # Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_BINARY_DIR}/src/engine/libengine.dll"      # <--this is in-file
        "${PROJECT_BINARY_DIR}/src/examples/engine-testbed/libengine.dll")