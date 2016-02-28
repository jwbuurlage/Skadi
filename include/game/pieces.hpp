#pragma once

#include <vector>
#include <string>
#include <memory>

#include "types.hpp"
#include "moves.hpp"

namespace Skadi {

class Board;

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

    virtual std::vector<Move> moves(int halfMoveNumber);
    virtual Move moveForTarget(int row, int col, int halfMoveNumber);

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

    void filterValidMovesInDirection(std::vector<int> di, std::vector<int> dj,
                                     std::vector<Move>& moves,
                                     int halfMoveNumber);
    void filterValidMoves(std::vector<int> di, std::vector<int> dj,
                          std::vector<Move>& moves, int halfMoveNumber);
};

class Pawn : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::pawn; }

    std::vector<Move> moves(int halfMove) override;
};

class Rook : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::rook; }

    std::vector<Move> moves(int halfMove) override;
};

class Knight : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::knight; }

    std::vector<Move> moves(int halfMove) override;
};

class Bishop : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::bishop; }

    std::vector<Move> moves(int halfMove) override;
};

class Queen : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::queen; }

    std::vector<Move> moves(int halfMove) override;
};

class King : public Piece {
  public:
    using Piece::Piece;
    ChessPiece getType() const override { return ChessPiece::king; }

    std::vector<Move> moves(int halfMove) override;
};

std::unique_ptr<Piece> createPiece(PieceObserver* game, Board* board,
                                   ChessPiece piece, int row, int col,
                                   Color color);

} // namespace Skadi
