cmake_minimum_required(VERSION 3.13)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
add_executable(untitled1 main.c test.c)

target_link_libraries(untitled1 ${CMAKE_DL_LIBS})

