#ifndef CHESS_KING_H
#define CHESS_KING_H
#include "Board.h"
#include"Piece.h"

class King: public Piece {
public:
    King(PieceColor color, int x, int y);
    bool isMoved(int t_x, int t_y, const BoardGrid& board) override;
    void draw(RenderWindow& window);
    void movement(RenderWindow& window, const BoardGrid& board, const Board& layout);

private:
    Texture texture;
    Sprite sprite{texture};
    bool moved{false};
    bool dragging{false};
    Vector2f dragOffset{0.f, 0.f};
    void movement(RenderWindow& window);
};


#endif
