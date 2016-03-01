#pragma once

#include <jw/logging.hpp>

#include "types.hpp"

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

    // are we free to check with this move
    virtual bool isFree() const { return true; }

    Square* getTarget() const;
    Piece* getPiece() const;

  protected:
    Game* game_;
    Board* board_;
    Piece* piece_;
    Square* target_;
    Square* original_;
    Piece* captured_;

    int halfMoveNumber_;
    int oldHalfMoveNumber_;
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

enum class CastlingType { castle_long, castle_short };

class CastlingMove : public Move {
  public:
    CastlingMove(Game* game, Board* board, Piece* piece, Square* target,
                 int moveNumber, CastlingType type)
        : Move(game, board, piece, target, moveNumber), type_(type) {}

    void make() override;

    bool isFree() const override { return false; }

  private:
    CastlingType type_;
};

class PromotionMove : public Move {
  public:
    PromotionMove(Game* game, Board* board, Piece* piece, Square* target,
                  int moveNumber, ChessPiece promotionPiece)
        : Move(game, board, piece, target, moveNumber),
          promotionPiece_(promotionPiece) {}

    void make() override;
    ChessPiece getPromotionPiece() const { return promotionPiece_; }

  private:
    ChessPiece promotionPiece_;
};

} // namespace Skadi
