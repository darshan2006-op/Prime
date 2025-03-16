cmake_minimum_required(VERSION 3.29)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

message(${EXECUTABLE_OUTPUT_PATH})

project(GameEngine)

add_subdirectory(Prime)
add_subdirectory(SandBox)
add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
