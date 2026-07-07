#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#pragma once
#include <SFML/Graphics.hpp>

class Board {
public:
    static float PawnSideDown_start_y, KingSideDown_start_y, KingSideUp_start_y, PawnSideUp_start_y;
    Board(float startX = 320.0f, float startY = 40.0f, float squareSize = 80.0f);
    void draw(sf::RenderWindow &window);
private:
    float m_startX;
    float m_startY;
    float m_squareSize;
    sf::Color m_Lcolor;
    sf::Color m_Dcolor;
    sf::RectangleShape m_square;
};


#endif //CHESS_BOARD_H
