#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "../../Board.h"
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(PieceColor color, int x, int y);
    bool isMoved(int t_x, int t_y, const BoardGrid& board) override;
    void draw(RenderWindow& window);
    bool movement(RenderWindow& window, const BoardGrid& board, const Board& layout);

private:
    Texture texture;
    Sprite sprite{texture};
    bool moved{false};
    bool dragging{false};
    Vector2f dragOffset{0.f, 0.f};
};


#endif //CHESS_KNIGHT_H
