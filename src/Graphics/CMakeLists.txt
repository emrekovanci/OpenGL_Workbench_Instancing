set(INCROOT ${PROJECT_SOURCE_DIR}/include/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Graphics)

set(SRC
    ${INCROOT}/PostProcess.hpp
    ${SRCROOT}/PostProcess.cpp
)

add_library(GraphicsLibrary STATIC ${SRC})

target_include_directories(GraphicsLibrary PUBLIC "${PROJECT_SOURCE_DIR}/include")

find_package(glad CONFIG REQUIRED)
target_link_libraries(GraphicsLibrary PRIVATE glad::glad)