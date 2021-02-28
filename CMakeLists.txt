cmake_minimum_required(VERSION 3.14)

project(ooptreevfs)

file(GLOB SRC include/*.hpp src/*.cpp lib/*.c lib/.h)
include_directories(include)
link_directories(include)
include_directories(lib)

add_executable(${PROJECT_NAME} ${SRC})
