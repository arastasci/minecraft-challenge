cmake_minimum_required(VERSION 3.3)
project(main)

include_directories(/usr/local/include)
include_directories(include)
include_directories(/opt/homebrew/include)

link_directories(/usr/local/lib)
link_directories(/opt/homebrew/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -w")

find_package(OpenGL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIRS}
) 

set(SOURCE_FILES src/main.cpp src/glad.c src/Shader.cpp)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES})
target_link_libraries(main glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)