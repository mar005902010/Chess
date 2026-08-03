cmake_minimum_required(VERSION 3.20)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)

add_executable(Chess main.cpp
        Board.cpp
        Board.h
        Piece.cpp
        Piece.h
        Pawn.cpp
        Pawn.h
        King.cpp
        King.h)

target_link_libraries(Chess PRIVATE SFML::Graphics SFML::Window SFML::System)