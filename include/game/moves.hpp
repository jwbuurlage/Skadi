#pragma once

#include <jw/logging.hpp>

namespace Skadi {

class Game;
class Board;
class Piece;
struct Square;

class Move {
  public:
    Move(Game* game, Board* board, Piece* piece, Square* target, int halfMoveNumber);

    virtual bool isLegal() const;
    virtual void make();
    void unmake();

    Square* getTarget() const;

  protected:
    Game* game_;
    Board* board_;
    Piece* piece_;
    Square* target_;

    int halfMoveNumber_;
};

class NullMove : public Move {
  public:
    NullMove() : Move(nullptr, nullptr, nullptr, nullptr, 0) {}
    void make() override { }
    bool isLegal() const override { return false; }
};

enum class EnPassantDirection { left, right };
class EnPassantMove : public Move {
  public:
    EnPassantMove(Game* game, Board* board, Piece* piece, Square* target,
         int halfMoveNumber, EnPassantDirection direction);
    void make() override;

  private:
    EnPassantDirection direction_;
};

class CastlingMove : public Move {
    CastlingMove(bool castleShort, Game* game, Board* board, int moveNumber)
        : Move(game, board, nullptr, nullptr, moveNumber) {}
};

} // namespace Skadi
