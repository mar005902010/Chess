#pragma once

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
using namespace sf;
using namespace std;

enum class PieceType {NONE, PAWN, KING, QUEEN, KNIGHT, BISHOP, ROOK};
enum class PieceColor {WHITE, BLACK, NO_COLOR};

class Piece;
using BoardGrid = vector<vector<shared_ptr<Piece>>>;

class Piece {
    protected:
        PieceType type;
        PieceColor color;
        int g_x, g_y;
        bool hasMoved;
        bool captured;
    public:
        Piece(PieceType type, PieceColor color, int x, int y);
        virtual ~Piece() = default;
        virtual bool isMoved(int t_x, int t_y, const BoardGrid& board)=0;

        PieceColor getColor() const;
        PieceType getType() const;
        int getX() const;
        int getY() const;
        bool getHasMoved() const;
        bool isCaptured() const;

        void setPosition(int x, int y);
        void capture();
};



class King: public Piece {
    public:
    King(PieceColor color, int x, int y);
    bool isMoved(int t_x, int t_y, const BoardGrid& board) override;
    void draw(RenderWindow& window);
};


#endif
