
add_library(engine SHARED defines.h core/logger.cpp core/logger.h core/assert.h platform/platform.h)
target_compile_definitions(engine PRIVATE ENGINE_EXPORT)
target_link_libraries(engine PRIVATE spdlog)
target_include_directories(engine PRIVATE .
        PUBLIC ${PROJECT_SOURCE_DIR}/src/3rdparty/spdlog/include
        )