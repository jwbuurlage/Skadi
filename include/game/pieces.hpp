#pragma once

#include <vector>
#include <string>
#include <memory>

#include "board.hpp"

namespace Skadi {

class Board;
class Game;

class PieceObserver {
  public:
    virtual void activate(Piece* piece) = 0;
    virtual void deactivate(Piece* piece) = 0;
};

class Piece {
  public:
    Piece(PieceObserver* game, Board* board, int row, int col, Color color);

    void move(int row, int col, int moveNumber);
    int getRow() const;
    int getColumn() const;

    virtual std::vector<Square*> targets();
    virtual bool canTarget(int row, int col);

    Color getColor() const;
    virtual ChessPiece getType() const;

    void capture();
    bool isCaptured() const;

  protected:
    PieceObserver* game_;
    Board* board_;

    int row_;
    int column_;
    Color color_;

    int lastMoved_ = 0;
    bool captured_ = false;

    void squaresForDirection(std::vector<int> di, std::vector<int> dj,
                             std::vector<Square*>& targets);
    void filterValidSquares(std::vector<int> di, std::vector<int> dj,
                            std::vector<Square*>& targets);
};

class Pawn : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::pawn; }

    std::vector<Square*> targets() override;
};

class Rook : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::rook; }

    std::vector<Square*> targets() override;
};

class Knight : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::knight; }

    std::vector<Square*> targets() override;
};

class Bishop : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::bishop; }

    std::vector<Square*> targets() override;
};

class Queen : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::queen; }

    std::vector<Square*> targets() override;
};

class King : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::king; }

    std::vector<Square*> targets() override;
};

std::unique_ptr<Piece> createPiece(PieceObserver* game, Board* board, ChessPiece piece,
                                   int row, int col, Color color);

} // namespace Skadi
