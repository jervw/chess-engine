cmake_minimum_required(VERSION 3.11.0)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_definitions("-DUNICODE -D_UNICODE")


add_executable(chess src/main.cc src/minmax.cc src/minmax.hh src/move.cc src/move.hh src/state.cc src/state.hh src/user_interface.cc src/user_interface.hh src/pawn.cc src/pawn.hh src/tile.cc src/tile.hh src/legal_moves.cc src/legal_moves.hh)
