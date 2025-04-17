project(glad)

include_directories(glad include/)
add_library(glad src/glad.c include/glad/glad.h include/KHR/khrplatform.h)