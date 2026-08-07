#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include <iostream>

using namespace sf;
using namespace std;



int main() {
    RenderWindow window(VideoMode({1280,720}), "chess");
    window.setFramerateLimit(60);
    Board board;
    auto king = make_shared<King>(PieceColor::BLACK, 4, 0);
    auto queen = make_shared<Queen>(PieceColor::BLACK, 3, 0);
    auto rook = make_shared<Rook>(PieceColor::BLACK, 0, 0);
    auto rook1 = make_shared<Rook>(PieceColor::BLACK, 7, 0);
    auto bishop = make_shared<Bishop>(PieceColor::BLACK, 2, 0);
    auto bishop1 = make_shared<Bishop>(PieceColor::BLACK, 5, 0);
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
        if (!king->isCaptured()) {
            boardGrid[king->getY()][king->getX()] = king;
        }
        if (!queen->isCaptured()) {
            boardGrid[queen->getY()][queen->getX()] = queen;
        }
        if (!rook->isCaptured()) {
            boardGrid[rook->getY()][rook->getX()] = rook;
        }
        if (!rook1->isCaptured()) {
            boardGrid[rook1->getY()][rook1->getX()] = rook1;
        }
        if (!bishop->isCaptured()) {
            boardGrid[bishop->getY()][bishop->getX()] = bishop;
        }
        if (!bishop1->isCaptured()) {
            boardGrid[bishop1->getY()][bishop1->getX()] = bishop1;
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
        const BoardGrid boardGrid = buildBoardGrid();
        king->movement(window, boardGrid, board);
        queen->movement(window, boardGrid, board);
        rook->movement(window, boardGrid, board);
        rook1->movement(window, boardGrid, board);
        bishop->movement(window, boardGrid, board);
        bishop1->movement(window, boardGrid, board);
        for (auto& pawn : pawns) {
            const BoardGrid boardGrid = buildBoardGrid();
            pawn->movement(window, boardGrid, board);
        }
        window.clear(Color::White);
        board.draw(window);
        king->draw(window);
        queen->draw(window);
        rook->draw(window);
        rook1->draw(window);
        bishop->draw(window);
        bishop1->draw(window);
        for (auto& pawn : pawns) {
            pawn->draw(window);
        }

        window.display();



    }

}
