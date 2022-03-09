cmake_minimum_required(VERSION 3.11.0)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-DUNICODE -D_UNICODE")


file(GLOB chess_SRC
    "src/*.hh"
    "src/*.cc"
)

add_executable(chess ${chess_SRC})
