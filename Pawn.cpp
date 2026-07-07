
#include "Piece.h"
#include "Board.h"
#include "Pawn.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;
#include <iostream>
using namespace std;

static Texture loadtexture(const std::string& path) {
    Texture texture;
    if (!texture.loadFromFile(path)) {
        cout<<"Error loading texture"<<std::endl;
    }
    return texture;
}

Pawn::Pawn(PieceColor color, int x, int y):Piece(PieceType::PAWN, color, x, y), texture(loadtexture("/Users/marius/CLionProjects/Chess/Pieces/Black/black_pawn.png")), sprite(texture) {
    sprite.setPosition({static_cast<float>(x), static_cast<float>(y)});
}

bool Pawn::isMoved(int t_x, int t_y, const BoardGrid &board) {
    if (t_x <0||t_y<0||t_x>=8||t_y>=8) return false;
    if (g_x==t_x && g_y==t_y) return false;

    int direction = (color == PieceColor::WHITE) ? -1 : 1;
    int startRow = (color == PieceColor::WHITE) ? 6 : 1;

    int deltaX = t_x - g_x;
    int deltaY = t_y - g_y;

    if (deltaX==0) {
        if (deltaY==direction) {
            return board[t_y][t_x]==nullptr;
        }
        if (!hasMoved && g_y==startRow && deltaY==direction*2) {
            int intermidiateY= g_y+direction;
            return (board[intermidiateY][t_x]==nullptr && board[t_y][t_x]==nullptr);
        }

    }

    if (abs(deltaX)==1 && deltaY==direction) {
        auto targetPiece = board[t_y][t_x];
        if (targetPiece != nullptr && targetPiece->getColor() != color) {
            return true;
        }

    }

    return false;
}

//Draw Pawn

void Pawn::draw(RenderWindow &window) {
    //Draw at starting position
    Texture texture("/Users/marius/CLionProjects/Chess/Pieces/Black/black_pawn.png");
    texture.setSmooth(true);
    Sprite pawn(texture);
    float pawn_x = 320;

    for (int i=1;i<=8;i++) {
        pawn.setPosition({pawn_x, Board::PawnSideDown_start_y});
        window.draw(pawn);
        pawn_x += 80;
    }


}

void Pawn::movement(RenderWindow &window) {

    const Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    const bool leftPressed = Mouse::isButtonPressed(Mouse::Button::Left);

    static bool dragging = false;
    static Vector2f dragOffset{0.f, 0.f};

    const FloatRect bounds = sprite.getGlobalBounds();

    if (leftPressed) {
        if (!dragging && bounds.contains(mousePos) && !moved) {
            dragging = true;
            dragOffset = mousePos - sprite.getPosition();
        }

        if (dragging) {
            Vector2f nextPos = mousePos - dragOffset;

            const float boardLeft = 320.f;
            const float boardTop = 40.f;
            const float boardRight = boardLeft + 8.f * 80.f - bounds.size.x;
            const float boardBottom = boardTop + 8.f * 80.f - bounds.size.y;

            if (nextPos.x <boardLeft) nextPos.x = boardLeft;
            if (nextPos.x >boardRight) nextPos.x = boardRight;
            if (nextPos.y <boardTop) nextPos.y = boardTop;
            if (nextPos.y >boardBottom) nextPos.y = boardBottom;

            sprite.setPosition(nextPos);
        }
    } else {
        if (dragging) {
            Vector2f releasePos = sprite.getPosition();

            const float boardLeft = 320.f;
            const float boardTop = 40.f;
            const float squareSize = 80.f;

            float snappedX = boardLeft + std::round((releasePos.x - boardLeft) / squareSize)*squareSize;
            float snappedY = boardTop + std::round((releasePos.y - boardTop) / squareSize)*squareSize;

            sprite.setPosition({snappedX, snappedY});

            int boardx = static_cast<int>((snappedX-boardLeft)/squareSize);
            int boardy = static_cast<int>((snappedY-boardTop)/squareSize);

            setPosition(boardx, boardy);
        }

        dragging = false;
        moved = false;
    }
    moved = leftPressed;

}

