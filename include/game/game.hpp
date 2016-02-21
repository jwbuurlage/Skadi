#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include "board.hpp"
#include "pieces.hpp"
#include "util/notation.hpp"

namespace Skadi {

struct CastlingRights {
    bool whiteQueenSide = true;
    bool whiteKingSide = true;
    bool blackQueenSide = true;
    bool blackKingSide = true;
};

class Game : public PieceObserver {
  public:
    std::vector<Piece*> getActivePieces() { return activePieces; }

    Board& getBoard() { return board_; }
    const Board& getBoard() const { return board_; }

    void activate(Piece* piece) override {
        activePieces.push_back(piece);
        activePiecesForColor[piece->getColor()].push_back(piece);
    }

    void deactivate(Piece* piece) override {
        activePieces.erase(
            std::remove(activePieces.begin(), activePieces.end(), piece),
            activePieces.end());

        activePiecesForColor[piece->getColor()].erase(
            std::remove(activePieces.begin(), activePieces.end(), piece),
            activePieces.end());
    }

    Color colorToMove() const {
        return (halfMove_ % 2 == 1) ? Color::white : Color::black;
    }

    void nextMove() {
        halfMove_ += 1;
        move_ = (halfMove_ - 1) / 2 + 1;
        fiftyMoves_ += 1;
    }

    int getHalfMove() const { return halfMove_; }
    void setHalfMove(int halfMove) { halfMove_ = halfMove; }

    void resetFiftyMoves(int moves = 0) {
        fiftyMoves_ = moves;
    }

    CastlingRights& getCastlingRights() { return castlingRights_; }

    void setEnPassentSquare(Square* square) { enPassentSquare = square; }
    void setMove(int move) { move_ = move; };

  private:
    std::vector<Piece*> activePieces;
    std::map<Color, std::vector<Piece*>> activePiecesForColor = {
        {Color::white, {}}, {Color::black, {}}};

    Board board_;

    int halfMove_ = 1;
    int move_ = 1;

    // fifty-move draw. we count double
    // so that a draw can be claimed when this reaches 100
    int fiftyMoves_ = 0;

    Square* enPassentSquare = nullptr;


    CastlingRights castlingRights_;
};

} // namespace Skadi
