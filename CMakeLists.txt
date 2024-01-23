cmake_minimum_required(VERSION 2.6)
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

add_executable(dshop ./src/main.cpp)
target_link_libraries(dshop ${OPENGL_LIBRARY} ${GLFW_LIBRARY} ${GLEW_LIBRARY})
