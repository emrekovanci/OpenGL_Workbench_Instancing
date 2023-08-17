set(INCROOT ${PROJECT_SOURCE_DIR}/include/Math)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/Math)

set(SRC
    ${INCROOT}/MathEffect.hpp
    ${SRCROOT}/MathEffect.cpp
    ${INCROOT}/MathEffectSelector.hpp
    ${SRCROOT}/MathEffectSelector.cpp
    ${INCROOT}/Graph.hpp
    ${SRCROOT}/Graph.cpp
)

add_library(MathEffectLibrary STATIC ${SRC})

target_include_directories(MathEffectLibrary PUBLIC "${PROJECT_SOURCE_DIR}/include")

find_package(glm CONFIG REQUIRED)
target_link_libraries(MathEffectLibrary PRIVATE glm::glm)