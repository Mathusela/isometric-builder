cmake_minimum_required(VERSION 3.0.0)
project(isometric-builder VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
link_directories(lib)

link_libraries(glfw3 opengl32 gdi32)

add_executable(isometric-builder src/main.cpp src/glad.c src/standard-functions.cpp src/tile.cpp src/terrain.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
