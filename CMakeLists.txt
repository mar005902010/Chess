cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/sfml/sfml
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML)

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
        Pieces/Scripts/Knight.h
        chess.h)

target_link_libraries(Chess PRIVATE SFML::Graphics SFML::Window SFML::System)
