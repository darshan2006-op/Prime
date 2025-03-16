cmake_minimum_required(VERSION 3.29)
project(Prime)
include_directories(Prime src/)
add_library(Prime src/Core/Core.h src/prime.h src/Core/Application.h src/Core/EntryPoint.cpp)
