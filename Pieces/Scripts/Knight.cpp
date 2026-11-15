#include "/Users/marius/CLionProjects/Chess/Pieces/Scripts/Knight.h"
#include "/Users/marius/CLionProjects/Chess/Pieces/Scripts/Piece.h"
#include "../../Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;
#include <iostream>
using namespace std;

static Texture loadTexture(const string& filename) {
    Texture texture;
    if (!texture.loadFromFile(filename)) {
        cout << "Error loading texture" << endl;
    }
    return texture;
}

Knight::Knight(PieceColor color, int x, int y) : Piece(PieceType::KNIGHT, color, x, y), texture(loadTexture(color == PieceColor::BLACK ? "/Users/marius/CLionProjects/Chess/Pieces/Colors/Black/black_knight.png" : "/Users/marius/CLionProjects/Chess/Pieces/Colors/White/white_knight.png")), sprite(texture) {
    sprite.setPosition({320.f + static_cast<float>(x)*80.f, 40.f + static_cast<float>(y)*80.f});
}

bool Knight::isMoved(int t_x, int t_y, const BoardGrid &board) {
    if (t_x<0||t_y<0||t_x>=8||t_y>=8) return false;

    int dx = abs(t_x-g_x);
    int dy = abs(t_y-g_y);

    if (!((dx==1&&dy==2)||(dx==2&&dy==1))) {
        return false;
    }

    auto targetPiece = board[t_y][t_x];
    return targetPiece == nullptr || targetPiece->getColor() != color;
}

void Knight::draw(RenderWindow& window) {
    window.draw(sprite);
}

bool Knight::movement(RenderWindow &window, const BoardGrid &board, const Board &layout) {
    const Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
    const bool leftPressed = Mouse::isButtonPressed(Mouse::Button::Left);
    const FloatRect bounds = sprite.getGlobalBounds();

    if (leftPressed) {
        if (!dragging && bounds.contains(mousePosition)&& !moved) {
            dragging = true;
            dragOffset = mousePosition - sprite.getPosition();
        }

        if (dragging) {
            Vector2f nextPos = mousePosition - dragOffset;
            const float boardLeft = 320.f;
            const float boardTop = 40.f;
            const float boardRight = boardLeft + 8.f*80.f-bounds.size.x;
            const float boardBottom = boardTop + 8.f*80.f-bounds.size.y;

            if (nextPos.x<boardLeft) nextPos.x = boardLeft;
            if (nextPos.x>boardRight) nextPos.x = boardRight;
            if (nextPos.y>boardBottom) nextPos.y = boardBottom;
            if (nextPos.y<boardTop) nextPos.y = boardTop;

            sprite.setPosition(nextPos);

        }
    }else {
        if (dragging) {
            Vector2f releasePos = sprite.getPosition();
            const float boardLeft = 320.f;
            const float boardTop = 40.f;
            const float squareSize = 80.f;

            float snappedX = boardLeft + round((releasePos.x - boardLeft)/squareSize)*squareSize;
            float snappedY = boardTop + round((releasePos.y - boardTop)/squareSize)*squareSize;

            int boardx = static_cast<int>((snappedX - boardLeft)/squareSize);
            int boardy = static_cast<int>((snappedY - boardTop)/squareSize);

            if (isMoved(boardx, boardy, board)) {
                auto targetPiece = board[boardy][boardx];
                if (targetPiece !=nullptr && targetPiece->getColor() != color) {
                    targetPiece->capture();
                }
                sprite.setPosition({snappedX, snappedY});
                setPosition(boardx, boardy);
                return true;
            }else {
                sprite.setPosition({320.f + static_cast<float>(g_x) * 80.f, 40.f + static_cast<float>(g_y) * 80.f});
            }
            dragging = false;
        }
    }
    moved = leftPressed;
    return false;
}



