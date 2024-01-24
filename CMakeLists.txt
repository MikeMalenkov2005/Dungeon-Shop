cmake_minimum_required(VERSION 3.8)
project(Dungeon-Shop)

find_package(OpenGL REQUIRED)

set(GLFW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glfw.h")
set(GLFW_LIBRARY "" CACHE FILEPATH "The path to glfw3.lib")

set(GLEW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glew.h")
set(GLEW_LIBRARY "" CACHE FILEPATH "The path to glew32s.lib")

set(GLM_INCLUDE_PATH "" CACHE PATH "The directory that contains glm/glm.hpp")

include_directories(
    ${GLFW_INCLUDE_PATH}
    ${GLEW_INCLUDE_PATH}
    ${GLM_INCLUDE_PATH}
)

file(GLOB SRC_FILES "./src/*.cpp")

add_executable(dshop ${SRC_FILES})
set_property(TARGET dshop PROPERTY CXX_STANDARD 17)
target_link_libraries(dshop ${OPENGL_LIBRARY} ${GLFW_LIBRARY} ${GLEW_LIBRARY})
add_custom_command(TARGET dshop POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)
