cmake_minimum_required(VERSION 3.8)

project(OpenGL_Workbench_Instancing)

add_subdirectory(src/Core)
add_subdirectory(src/Math)
add_subdirectory(src/Graphics)

add_executable(${PROJECT_NAME} Main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

target_link_libraries(${PROJECT_NAME} PRIVATE CoreLibrary MathEffectLibrary GraphicsLibrary)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)