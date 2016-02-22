#pragma once

#include <jw/logging.hpp>

#include "game.hpp"
#include "pieces.hpp"
#include "board.hpp"

namespace Skadi {

class Move {
  public:
    Move(Game* game, Board* board, Piece* piece, Square* target, int moveNumber);

    bool isLegal() const;
    virtual void make();
    void unmake();

  protected:
    Game* game_;
    Board* board_;
    Piece* piece_;
    Square* target_;

    int moveNumber_;
};

class NullMove : public Move{
  public:
    NullMove() : Move(nullptr, nullptr, nullptr, nullptr, 0) {}
    void make() override { }
};

class EnPassentMove : public Move {

};

class CastlingMove : public Move {
    CastlingMove(bool castleShort, Game* game, Board* board, int moveNumber)
        : Move(game, board, nullptr, nullptr, moveNumber) {}
};

} // namespace Skadi
