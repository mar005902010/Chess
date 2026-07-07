#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "Piece.h"


class Pawn:public Piece {
public:
    Pawn(PieceColor color, int x, int y);
    bool isMoved(int t_x, int t_y, const BoardGrid& board) override;
    void draw(RenderWindow& window);
    void movement(RenderWindow& window);

private:
    Texture texture;
    Sprite sprite{texture};
    bool moved=false;
    bool dragging =false;
    Vector2f dragOffset{0.f,0.f};
};

#endif
