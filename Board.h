#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#pragma once
#include <SFML/Graphics.hpp>

class Board {
public:
    inline static constexpr float DefaultStartX = 320.0f;
    inline static constexpr float DefaultStartY = 40.0f;
    inline static constexpr float DefaultSquareSize = 80.0f;

    static float PawnSideDown_start_y, KingSideDown_start_y, KingSideUp_start_y, PawnSideUp_start_y;
    Board(float startX = DefaultStartX, float startY = DefaultStartY, float squareSize = DefaultSquareSize);
    void draw(sf::RenderWindow &window);
    float getStartX() const;
    float getStartY() const;
    float getSquareSize() const;
private:
    float m_startX;
    float m_startY;
    float m_squareSize;
    sf::Color m_Lcolor;
    sf::Color m_Dcolor;
    sf::RectangleShape m_square;
};


#endif //CHESS_BOARD_H
