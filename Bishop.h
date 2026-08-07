#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "Board.h"
#include "Piece.h"


class Bishop : public Piece {
public:
    Bishop(PieceColor color, int x, int y);
    bool isMoved(int t_x, int t_y, const BoardGrid& board) override;
    void draw(RenderWindow& window);
    void movement(RenderWindow& window, const BoardGrid& board, const Board& layout);

private:
    Texture texture;
    Sprite sprite{texture};
    bool moved{false};
    bool dragging{false};
    Vector2f dragOffset{0.f, 0.f};
};


#endif //CHESS_BISHOP_H
