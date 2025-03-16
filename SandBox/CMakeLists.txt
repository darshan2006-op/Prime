cmake_minimum_required(VERSION 3.29)

find_package(OpenGL REQUIRED)

project(SandBox)
link_libraries(glfw)
link_libraries(glad)
link_libraries(Prime)
link_libraries(OpenGL::GL)
include_directories(../deps/spdlog/include)
include_directories(../deps/glad/include)
include_directories(../Prime/src)
add_executable(SandBox src/main.cpp)
