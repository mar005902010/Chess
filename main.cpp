#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pawn.h"
#include <iostream>

using namespace sf;
using namespace std;



int main() {
    RenderWindow window(VideoMode({1280,720}), "chess");
    window.setFramerateLimit(60);
    Board board;
    Pawn pawn(PieceColor::WHITE, 0,1);

    while (window.isOpen()) {

        while (const optional <Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();

            else if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                if (keyPressed->scancode == Keyboard::Scancode::Escape) window.close();
            }
        }
        pawn.movement(window);
        window.clear(Color::White);
        board.draw(window);
        pawn.draw(window);

        window.display();



    }

}