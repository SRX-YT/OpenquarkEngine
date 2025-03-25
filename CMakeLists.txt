cmake_minimum_required(VERSION 4.0.0)
project(OpenQuark)

set(CMAKE_CXX_STANDARD 17)

# LIBRARIES
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/lib/glfw)
set(GLEW_DIR ${CMAKE_SOURCE_DIR}/lib/glew)

# GLFW
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION ${GLFW_DIR}/lib/glfw3.lib
    INTERFACE_INCLUDE_DIRECTORIES ${GLFW_DIR}/include  
)

# GLEW
add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION ${GLEW_DIR}/lib/glew32s.lib
    INTERFACE_INCLUDE_DIRECTORIES ${GLEW_DIR}/include
)

set(SOURCE_FILES main.cpp)
set(SRC_FOLDER src/)

add_executable(${PROJECT_NAME} ${SRC_FOLDER}/${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    glfw
    glew
    opengl32.lib
)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${GLEW_DIR}/bin/glew32.dll
    ${CMAKE_BINARY_DIR}/Release/
)