cmake_minimum_required(VERSION 3.8)
project(phdterm)
set(CMAKE_C_STANDARD 99)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw3)

file(GLOB SOURCE
    src/main.c)


add_executable(phdterm ${SOURCE} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(phdterm glfw ${OPENGL_LIBRARIES})
