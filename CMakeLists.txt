cmake_minimum_required(VERSION 3.8)
project(phdterm)
set(CMAKE_C_STANDARD 99)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glad)
add_subdirectory(external/glfw3)

add_definitions(-DDEBUG_PRINT=${DEBUG_PRINT})
if(DEBUG_PRINT)
  add_definitions(-D_DEBUG)
  add_compile_options(-Wall -Wextra)
endif()

file(GLOB SOURCE
    src/debug_print.h
    src/window_event.h
    src/window_event.c
    src/term_window.h
    src/term_window.c
    src/file_ops.h
    src/fileops_linux.c
    src/file_util.h
    src/file_util.c
    src/gl_utils.h
    src/gl_utils.c
    src/main.c)

add_executable(phdterm ${SOURCE} ${OPENGL_INCLUDE_DIRS})
target_link_libraries(phdterm glfw glad ${OPENGL_LIBRARIES})
