cmake_minimum_required(VERSION 3.29)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "/utf-8")
set(CMAKE_C_FLAGS "/utf-8")

message(${EXECUTABLE_OUTPUT_PATH})

project(GameEngine)

add_subdirectory(Prime)
add_subdirectory(SandBox)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/spdlog)
