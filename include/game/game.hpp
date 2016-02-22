#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include "board.hpp"
#include "pieces.hpp"
#include "util/notation.hpp"

namespace Skadi {

struct CastlingRights {
    bool whiteQueenSide = false;
    bool whiteKingSide = false;
    bool blackQueenSide = false;
    bool blackKingSide = false;
};

class Game : public PieceObserver {
  public:
    std::vector<Piece*> getActivePieces();

    Board& getBoard();
    const Board& getBoard() const;

    void activate(Piece* piece) override;

    void deactivate(Piece* piece) override;
    Color colorToMove() const;

    void nextMove();

    int getHalfMove() const;
    void setHalfMove(int halfMove);

    void resetFiftyMoves(int moves = 0);

    CastlingRights& getCastlingRights();

    void setEnPassentSquare(Square* square);
    void setMove(int move);

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
