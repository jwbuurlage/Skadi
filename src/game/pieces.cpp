#include <cmath>

#include "game/pieces.hpp"
#include "game/board.hpp"
#include "game/moves.hpp"

namespace Skadi {

Piece::Piece(PieceObserver* game, Board* board, int row, int col, Color color)
    : game_(game), board_(board), row_(row), column_(col), color_(color) {
    game_->activate(this);
    board_->getSquare(row_, column_)->piece = this;
}

void Piece::move(int row, int col, int moveNumber) {
    // remove from current square
    board_->getSquare(row_, column_)->piece = nullptr;

    // add to new square
    board_->getSquare(row, col)->piece = this;

    // update position
    row_ = row;
    column_ = col;
    lastMoved_ = moveNumber;
}

int Piece::getRow() const { return row_; }
int Piece::getColumn() const { return column_; }

std::vector<std::unique_ptr<Move>> Piece::moves(int) {
    return std::vector<std::unique_ptr<Move>>();
}

ChessPiece Piece::getType() const { return ChessPiece::none; }
int Piece::getLastMoved() const { return lastMoved_; }

std::unique_ptr<Move> Piece::moveForTarget(int row, int col, int halfMoveNumber) {
    for (auto& move : moves(halfMoveNumber)) {
        if (move->getTarget()->row == row && move->getTarget()->column == col)
            return std::move(move);
    }
    return std::make_unique<NullMove>();
}

Color Piece::getColor() const { return color_; }

void Piece::capture() {
    game_->deactivate(this);
    board_->getSquare(row_, column_)->piece = nullptr;
    row_ = -1;
    column_ = 1;
    captured_ = true;
}

bool Piece::isCaptured() const { return captured_; }

void Piece::filterValidMovesInDirection(
    std::vector<int> di, std::vector<int> dj,
    std::vector<std::unique_ptr<Move>>& moves, int halfMoveNumber) {
    for (size_t k = 0; k < di.size(); ++k) {
        for (int i = row_ + di[k], j = column_ + dj[k];
             i >= 0 && i < board_->getSize() && j >= 0 && j < board_->getSize();
             i += di[k], j += dj[k]) {
            auto square = board_->getSquare(i, j);
            if (square->piece != nullptr) {
                if (square->piece->getColor() != color_)
                    moves.push_back(
                        std::make_unique<Move>((Game*)game_, board_, this, square, halfMoveNumber));
                break;
            }
            moves.push_back(
                std::make_unique<Move>((Game*)game_, board_, this, square, halfMoveNumber));
        }
    }
}

void Piece::filterValidMoves(std::vector<int> di, std::vector<int> dj,
                             std::vector<std::unique_ptr<Move>>& moves,
                             int halfMoveNumber) {
    for (size_t k = 0; k < di.size(); ++k) {
        int i = row_ + di[k];
        int j = column_ + dj[k];
        if (i >= 0 && i < board_->getSize() && j >= 0 &&
            j < board_->getSize()) {
            auto square = board_->getSquare(i, j);
            if (square->piece != nullptr) {
                if (square->piece->getColor() != color_)
                    moves.push_back(
                        std::make_unique<Move>((Game*)game_, board_, this, square, halfMoveNumber));
            } else {
                moves.push_back(
                    std::make_unique<Move>((Game*)game_, board_, this, square, halfMoveNumber));
            }
        }
    }
}

std::vector<std::unique_ptr<Move>> Pawn::moves(int halfMoveNumber) {
    std::vector<std::unique_ptr<Move>> moves;

    // the target row is always one 'forward'
    auto targetRow = (color_ == Color::white) ? row_ + 1 : row_ - 1;

    // can capture left
    if (column_ > 0) {
        auto leftSquare = board_->getSquare(targetRow, column_ - 1);
        if (leftSquare->piece != nullptr) {
            moves.push_back(
                std::make_unique<Move>((Game*)game_, board_, this, leftSquare, halfMoveNumber));
        } else {
            // can we capture en-passant
            auto leftEnPassant = board_->getSquare(row_, column_ - 1);
            if (leftEnPassant->piece != nullptr &&
                leftEnPassant->piece->getType() == ChessPiece::pawn &&
                leftEnPassant->piece->getLastMoved() == halfMoveNumber - 1 &&
                ((Pawn*)leftEnPassant->piece)->didMoveDouble()) {
                moves.push_back(std::make_unique<EnPassantMove>(
                    (Game*)game_, board_, this, leftSquare, halfMoveNumber,
                    EnPassantDirection::left));
            }
        }
    }

    // can capture right
    if (column_ < board_->getSize() - 1) {
        auto rightSquare = board_->getSquare(targetRow, column_ + 1);
        if (rightSquare->piece != nullptr) {
            moves.push_back(
                std::make_unique<Move>((Game*)game_, board_, this, rightSquare, halfMoveNumber));
        } else {
            // can we capture en-passant
            auto rightEnPassant = board_->getSquare(row_, column_ + 1);
            if (rightEnPassant->piece != nullptr &&
                rightEnPassant->piece->getType() == ChessPiece::pawn &&
                rightEnPassant->piece->getLastMoved() == halfMoveNumber - 1 &&
                ((Pawn*)rightEnPassant->piece)->didMoveDouble()) {
                moves.push_back(std::make_unique<EnPassantMove>(
                    (Game*)game_, board_, this, rightSquare, halfMoveNumber,
                    EnPassantDirection::right));
            }
        }

    }

    // can move forward
    auto forwardSquare = board_->getSquare(targetRow, column_);
    if (forwardSquare->piece == nullptr) {
        moves.push_back(std::make_unique<Move>((Game*)game_, board_, this, forwardSquare,
                             halfMoveNumber));
        // if not moved yet, can move two
        if (lastMoved_ == 0) {
            auto targetRowNext = (color_ == Color::white) ? row_ + 2 : row_ - 2;
            auto nextForwardSquare = board_->getSquare(targetRowNext, column_);
            if (nextForwardSquare->piece == nullptr)
                moves.push_back(std::make_unique<Move>((Game*)game_, board_, this,
                                     nextForwardSquare, halfMoveNumber));
        }
    }


    return moves;
}

void Pawn::move(int row, int col, int moveNumber) {
    if (std::abs(row_ - row) == 2) {
        movedDouble_ = true;
    }
    Piece::move(row, col, moveNumber);
}

std::vector<std::unique_ptr<Move>> Rook::moves(int halfMoveNumber) {
    std::vector<std::unique_ptr<Move>> moves;
    filterValidMovesInDirection({0, 1, 0, -1}, {-1, 0, 1, 0}, moves, halfMoveNumber);
    return moves;
}

std::vector<std::unique_ptr<Move>> Knight::moves(int halfMoveNumber) {
    std::vector<std::unique_ptr<Move>> moves;
    filterValidMoves({2, 2, 1, 1, -1, -1, -2, -2}, {1, -1, 2, -2, 2, -2, 1, -1},
                     moves, halfMoveNumber);
    return moves;
}

std::vector<std::unique_ptr<Move>> Bishop::moves(int halfMoveNumber) {
    std::vector<std::unique_ptr<Move>> moves;
    filterValidMovesInDirection({1, -1, 1, -1}, {1, 1, -1, -1}, moves,
                                halfMoveNumber);
    return moves;
}

std::vector<std::unique_ptr<Move>> Queen::moves(int halfMoveNumber) {
    std::vector<std::unique_ptr<Move>> moves;
    filterValidMovesInDirection({0, 1, 0, -1, 1, -1, 1, -1},
                                {-1, 0, 1, 0, 1, 1, -1, -1}, moves,
                                halfMoveNumber);
    return moves;
}

std::vector<std::unique_ptr<Move>> King::moves(int halfMoveNumber) {
    std::vector<std::unique_ptr<Move>> moves;
    filterValidMoves({1, 1, 1, 0, 0, -1, -1, -1}, {1, 0, -1, 1, -1, 1, 0, -1},
                     moves, halfMoveNumber);

    // FIXME check if long castle is still valid
    // FIXME can not castle through check

    return moves;
}

std::unique_ptr<Piece> createPiece(PieceObserver* game, Board* board, ChessPiece piece,
                                   int row, int col, Color color) {
    switch (piece) {
    case ChessPiece::pawn:
        return std::make_unique<Pawn>(game, board, row, col, color);
        break;

    case ChessPiece::rook:
        return std::make_unique<Rook>(game, board, row, col, color);
        break;

    case ChessPiece::knight:
        return std::make_unique<Knight>(game, board, row, col, color);
        break;

    case ChessPiece::bishop:
        return std::make_unique<Bishop>(game, board, row, col, color);
        break;

    case ChessPiece::queen:
        return std::make_unique<Queen>(game, board, row, col, color);
        break;

    case ChessPiece::king:
        return std::make_unique<King>(game, board, row, col, color);
        break;

    default:
        return std::make_unique<Pawn>(game, board, row, col, color);
        break;
    }
}

} // namespace Skadi
