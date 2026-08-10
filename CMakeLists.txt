cmake_minimum_required(VERSION 3.20)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3.0.2 COMPONENTS Graphics Window System REQUIRED)

add_executable(Chess main.cpp
        Board.cpp
        Board.h
        Pieces/Scripts/Piece.cpp
        Pieces/Scripts/Piece.h
        Pieces/Scripts/Pawn.cpp
        Pieces/Scripts/Pawn.h
        Pieces/Scripts/King.cpp
        Pieces/Scripts/King.h
        Pieces/Scripts/Queen.cpp
        Pieces/Scripts/Queen.h
        Pieces/Scripts/Rook.cpp
        Pieces/Scripts/Rook.h
        Pieces/Scripts/Bishop.cpp
        Pieces/Scripts/Bishop.h
        Pieces/Scripts/Knight.cpp
        Pieces/Scripts/Knight.h)

target_link_libraries(Chess PRIVATE SFML::Graphics SFML::Window SFML::System)