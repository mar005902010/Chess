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

    std::vector<std::shared_ptr<Pawn>> pawns;
    for (int i=0; i<8;++i) {
        pawns.emplace_back(std::make_shared<Pawn>(PieceColor::BLACK, i, 1));
    }

    auto buildBoardGrid = [&]() {
        BoardGrid boardGrid(8, std::vector<std::shared_ptr<Piece>>(8));
        for (const auto& pawn : pawns) {
            if (pawn->isCaptured()) {
                continue;
            }
            boardGrid[pawn->getY()][pawn->getX()] = pawn;
        }
        return boardGrid;
    };

    while (window.isOpen()) {

        while (const optional <Event> event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();

            else if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) {
                if (keyPressed->scancode == Keyboard::Scancode::Escape) window.close();
            }
        }
        for (auto& pawn : pawns) {
            const BoardGrid boardGrid = buildBoardGrid();
            pawn->movement(window, boardGrid, board);
        }
        window.clear(Color::White);
        board.draw(window);
        for (auto& pawn : pawns) {
            pawn->draw(window);
        }

        window.display();



    }

}
