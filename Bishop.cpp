#include "Bishop.h"
#include"Piece.h"
#include"Board.h"
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

Bishop::Bishop(PieceColor color, int x, int y) : Piece(PieceType::KING, color, x, y), texture(loadTexture("/Users/marius/CLionProjects/Chess/Pieces/Black/black_bishop.png")), sprite(texture) {
    sprite.setPosition({320.f + static_cast<float>(x)*80.f, 40.f + static_cast<float>(y)*80.f});
}

bool Bishop::isMoved(int t_x, int t_y, const BoardGrid &board) {
    if (t_x<0||t_y<0||t_x>=8||t_y>=8) return false;
    if (t_x == g_x && t_y == g_y) return false;

    int delta_x = t_x - g_x;
    int delta_y = t_y - g_y;

    bool diagonal=(abs(delta_x) == abs(delta_y));

    if (!diagonal) return false;

    int stepX, stepY;

    if (delta_x == 0) stepX = 0;
    else if (delta_x>0) stepX = 1;
    else stepX = -1;

    if (delta_y == 0) stepY = 0;
    else if (delta_y>0) stepY = 1;
    else stepY = -1;

    int x = g_x + stepX;
    int y = g_y + stepY;

    while (x!= t_x || y!= t_y) {
        if (board[y][x] != nullptr) {
            return false;
        }
        x+=stepX;
        y+=stepY;
    }

    auto targetPice = board[t_y][t_x];
    return targetPice == nullptr || targetPice->getColor() != color;
}

void Bishop::draw(RenderWindow& window) {
    window.draw(sprite);
}

void Bishop::movement(RenderWindow &window, const BoardGrid &board, const Board &layout) {
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
                sprite.setPosition({snappedX, snappedY});
                setPosition(boardx, boardy);
            }else {
                sprite.setPosition({320.f + static_cast<float>(g_x) * 80.f, 40.f + static_cast<float>(g_y) * 80.f});
            }
            dragging = false;
        }
    }
    moved = leftPressed;
}




