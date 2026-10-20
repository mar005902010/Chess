#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pieces/Scripts/Pawn.h"
#include "Pieces/Scripts/King.h"
#include "Pieces/Scripts/Queen.h"
#include "Pieces/Scripts/Rook.h"
#include "Pieces/Scripts/Bishop.h"
#include "Pieces/Scripts/Knight.h"
#include "chess.h"

using namespace sf;
using namespace std;



int main() {
    RenderWindow window(VideoMode({1280,720}), "chess");
    window.setFramerateLimit(60);
    Board board;
    //Black Pieces
    auto king = make_shared<King>(PieceColor::BLACK, 4, 0);
    auto queen = make_shared<Queen>(PieceColor::BLACK, 3, 0);
    auto rook = make_shared<Rook>(PieceColor::BLACK, 0, 0);
    auto rook1 = make_shared<Rook>(PieceColor::BLACK, 7, 0);
    auto bishop = make_shared<Bishop>(PieceColor::BLACK, 2, 0);
    auto bishop1 = make_shared<Bishop>(PieceColor::BLACK, 5, 0);
    auto knight = make_shared<Knight>(PieceColor::BLACK, 1, 0);
    auto knight1 = make_shared<Knight>(PieceColor::BLACK, 6, 0);
    std::vector<std::shared_ptr<Pawn>> pawns;
    for (int i=0; i<8;++i) {
        pawns.emplace_back(std::make_shared<Pawn>(PieceColor::BLACK, i, 1));
    }
    //White Pieces
    auto wking = make_shared<King>(PieceColor::WHITE, 4, 7);
    auto wqueen = make_shared<Queen>(PieceColor::WHITE, 3, 7);
    auto wrook = make_shared<Rook>(PieceColor::WHITE, 0, 7);
    auto wrook1 = make_shared<Rook>(PieceColor::WHITE, 7, 7);
    auto wbishop = make_shared<Bishop>(PieceColor::WHITE, 2, 7);
    auto wbishop1 = make_shared<Bishop>(PieceColor::WHITE, 5, 7);
    auto wknight = make_shared<Knight>(PieceColor::WHITE, 1, 7);
    auto wknight1 = make_shared<Knight>(PieceColor::WHITE, 6, 7);

    for (int i = 0; i<8; ++i) {
        pawns.emplace_back(std::make_shared<Pawn>(PieceColor::WHITE, i, 6));
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
        if (!knight->isCaptured()) {
            boardGrid[knight->getY()][knight->getX()] = knight;
        }
        if (!knight1->isCaptured()) {
            boardGrid[knight1->getY()][knight1->getX()] = knight1;
        }
        if (!wking->isCaptured()) {
            boardGrid[wking->getY()][wking->getX()] = wking;
        }
        if (!wbishop->isCaptured()) {
            boardGrid[wbishop->getY()][wbishop->getX()] = wbishop;
        }
        if (!wbishop1->isCaptured()) {
            boardGrid[wbishop1->getY()][wbishop1->getX()] = wbishop1;
        }
        if (!wknight->isCaptured()) {
            boardGrid[wknight->getY()][wknight->getX()] = wknight;
        }
        if (!wknight1->isCaptured()) {
            boardGrid[wknight1->getY()][wknight1->getX()] = wknight1;
        }
        if (!wrook->isCaptured()) {
            boardGrid[wrook->getY()][wrook->getX()] = wrook;
        }
        if (!wrook1->isCaptured()) {
            boardGrid[wrook1->getY()][wrook1 -> getX()]=wrook1;
        }
        if (!wqueen->isCaptured()) {
            boardGrid[wqueen->getY()][wqueen->getX()]=wqueen;
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
        //B Movement
        king->movement(window, boardGrid, board);
        queen->movement(window, boardGrid, board);
        rook->movement(window, boardGrid, board);
        rook1->movement(window, boardGrid, board);
        bishop->movement(window, boardGrid, board);
        bishop1->movement(window, boardGrid, board);
        knight->movement(window, boardGrid, board);
        knight1->movement(window, boardGrid, board);
        //W movement
        wking->movement(window, boardGrid, board);
        wqueen->movement(window, boardGrid, board);
        wrook->movement(window, boardGrid, board);
        wrook1->movement(window, boardGrid, board);
        wbishop->movement(window, boardGrid, board);
        wbishop1->movement(window, boardGrid, board);
        wknight->movement(window, boardGrid, board);
        wknight1->movement(window, boardGrid, board);

        for (auto& pawn : pawns) {
            const BoardGrid boardGrid = buildBoardGrid();
            pawn->movement(window, boardGrid, board);
        }
        window.clear(Color::White);
        board.draw(window);
        //B Draw
        if (!king->isCaptured()) {
            king->draw(window);
        }
        if (!queen->isCaptured()) {
            queen->draw(window);
        }
        if (!rook->isCaptured()) {
            rook->draw(window);
        }
        if (!rook1->isCaptured()) {
            rook1->draw(window);
        }
        if (!bishop->isCaptured()) {
            bishop->draw(window);
        }
        if (!bishop1->isCaptured()) {
            bishop1->draw(window);
        }
        if (!knight->isCaptured()) {
            knight->draw(window);
        }
        if (!knight1->isCaptured()) {
            knight1->draw(window);
        }
        //W Draw
        if (!wking->isCaptured()) {
            wking->draw(window);
        }
        if (!wqueen->isCaptured()) {
            wqueen->draw(window);
        }
        if (!wrook->isCaptured()) {
            wrook->draw(window);
        }
        if (!wrook1->isCaptured()) {
            wrook1->draw(window);
        }
        if (!wbishop->isCaptured()) {
            wbishop->draw(window);
        }
        if (!wbishop1->isCaptured()) {
            wbishop1->draw(window);
        }
        if (!wknight->isCaptured()) {
            wknight->draw(window);
        }
        if (!wknight1->isCaptured()) {
            wknight1->draw(window);
        }

        for (auto& pawn : pawns) {
            if (!pawn->isCaptured()) {
                pawn->draw(window);
            }
        }

        window.display();



    }

}
