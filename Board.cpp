#include "Board.h"

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

float Board::KingSideDown_start_y=0;
float Board::KingSideUp_start_y=0;
float Board::PawnSideDown_start_y=0;
float Board::PawnSideUp_start_y=0;



Board::Board(float startX, float startY, float squareSize)
    :m_startX(startX),
    m_startY(startY),
    m_squareSize(squareSize),
    m_Lcolor(238, 238, 210),
    m_Dcolor(128, 128, 128)
{
    m_square.setSize({m_squareSize, m_squareSize});
}

void Board::draw(RenderWindow& window) {
    for (int row=0; row<8;++row) {
        for (int col=0; col<8;++col) {
            if ((row+col)%2==0) {
                m_square.setFillColor(m_Lcolor);
            }else {
                m_square.setFillColor(m_Dcolor);
            }

            float posX = m_startX + col*m_squareSize;
            float posY = m_startY + row*m_squareSize;

            if (posY == 40) KingSideUp_start_y = posY;
            if (posY == 120) PawnSideUp_start_y = posY;
            if (posY == 520) PawnSideDown_start_y = posY;
            if (posY == 600) KingSideDown_start_y = posY;

            m_square.setPosition({posX, posY});
            window.draw(m_square);
        }
    }
}

float Board::getStartX() const {
    return m_startX;
}

float Board::getStartY() const {
    return m_startY;
}

float Board::getSquareSize() const {
    return m_squareSize;
}
