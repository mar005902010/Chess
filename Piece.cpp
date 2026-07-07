#include <cmath>
#include "Piece.h"
#include "Board.h"

Piece::Piece(PieceType pieceT, PieceColor c, int pieceX, int pieceY)
    :type(pieceT), color(c), g_x(pieceX), g_y(pieceY), hasMoved(false){}

PieceColor Piece::getColor() const  { return color; }
PieceType Piece::getType() const  { return type; }
int Piece::getX() const  { return g_x; }
int Piece::getY() const  { return g_y; }
bool Piece::getHasMoved() const  { return hasMoved; }

void Piece::setPosition(int x, int y) {
    g_x = x;
    g_y = y;
    hasMoved = true;
}

