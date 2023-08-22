set(INCROOT ${PROJECT_SOURCE_DIR}/include/Core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Core)

set(SRC
    ${INCROOT}/Vertex.hpp
    ${INCROOT}/Camera.hpp
    ${SRCROOT}/Camera.cpp
    ${INCROOT}/FrameRateCounter.hpp
    ${SRCROOT}/FrameRateCounter.cpp
    ${INCROOT}/Shader.hpp
    ${SRCROOT}/Shader.cpp
    ${INCROOT}/Texture2D.hpp
    ${SRCROOT}/Texture2D.cpp
    ${INCROOT}/VertexArray.hpp
    ${SRCROOT}/VertexArray.cpp
    ${INCROOT}/Buffers/VertexBuffer.hpp
    ${SRCROOT}/Buffers/VertexBuffer.cpp
    ${INCROOT}/Buffers/RenderBuffer.hpp
    ${SRCROOT}/Buffers/RenderBuffer.cpp
    ${INCROOT}/Buffers/FrameBuffer.hpp
    ${SRCROOT}/Buffers/FrameBuffer.cpp
)

add_library(CoreLibrary STATIC ${SRC})

target_include_directories(CoreLibrary PUBLIC "${PROJECT_SOURCE_DIR}/include")

find_package(glad CONFIG REQUIRED)
target_link_libraries(CoreLibrary PRIVATE glad::glad)

find_package(glm CONFIG REQUIRED)
target_link_libraries(CoreLibrary PRIVATE glm::glm)