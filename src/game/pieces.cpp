#include "game/pieces.hpp"

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

std::vector<Square*> Piece::targets() { return std::vector<Square*>(); }

ChessPiece Piece::getType() const { return ChessPiece::none; }

bool Piece::canTarget(int row, int col) {
    for (auto square : targets()) {
        if (square->row == row && square->column == col)
            return true;
    }
    return false;
}

Color Piece::getColor() const { return color_; }

void Piece::capture() {
    game_->deactivate(this);
    row_ = -1;
    column_ = 1;
    captured_ = true;
}

bool Piece::isCaptured() const { return captured_; }

void Piece::squaresForDirection(std::vector<int> di, std::vector<int> dj,
                         std::vector<Square*>& targets) {
    for (size_t k = 0; k < di.size(); ++k) {
        for (int i = row_ + di[k], j = column_ + dj[k];
             i >= 0 && i < board_->getSize() && j >= 0 && j < board_->getSize();
             i += di[k], j += dj[k]) {
            auto square = board_->getSquare(i, j);
            if (square->piece != nullptr) {
                if (square->piece->getColor() != color_)
                    targets.push_back(square);
                break;
            }
            targets.push_back(square);
        }
    }
}

void Piece::filterValidSquares(std::vector<int> di, std::vector<int> dj,
                        std::vector<Square*>& targets) {
    for (size_t k = 0; k < di.size(); ++k) {
        int i = row_ + di[k];
        int j = column_ + dj[k];
        if (i >= 0 && i < board_->getSize() && j >= 0 &&
            j < board_->getSize()) {
            auto square = board_->getSquare(i, j);
            if (square->piece != nullptr) {
                if (square->piece->getColor() != color_)
                    targets.push_back(square);
            } else {
                targets.push_back(square);
            }
        }
    }
}


std::vector<Square*> Pawn::targets() {
    std::vector<Square*> targets;

    // the target row is always one 'forward'
    auto targetRow = (color_ == Color::white) ? row_ + 1 : row_ - 1;

    // can capture left
    if (column_ > 0) {
        auto leftSquare = board_->getSquare(targetRow, column_ - 1);
        if (leftSquare->piece != nullptr) {
            targets.push_back(leftSquare);
        }
    }

    // can capture right
    if (column_ < board_->getSize() - 1) {
        auto rightSquare = board_->getSquare(targetRow, column_ + 1);
        if (rightSquare->piece != nullptr) {
            targets.push_back(rightSquare);
        }
    }

    // can move forward
    auto forwardSquare = board_->getSquare(targetRow, column_);
    if (forwardSquare->piece == nullptr) {
        targets.push_back(forwardSquare);
        // if not moved yet, can move two
        if (lastMoved_ == 0) {
            auto targetRowNext = (color_ == Color::white) ? row_ + 2 : row_ - 2;
            auto nextForwardSquare = board_->getSquare(targetRowNext, column_);
            if (nextForwardSquare->piece == nullptr)
                targets.push_back(nextForwardSquare);
        }
    }

    // FIXME: can capture en passent
    // ...

    return targets;
}

std::vector<Square*> Rook::targets() {
    std::vector<Square*> targets;
    squaresForDirection({0, 1, 0, -1}, {-1, 0, 1, 0}, targets);
    return targets;
}

std::vector<Square*> Knight::targets() {
    std::vector<Square*> targets;
    filterValidSquares({2, 2, 1, 1, -1, -1, -2, -2},
                       {1, -1, 2, -2, 2, -2, 1, -1}, targets);
    return targets;
}

std::vector<Square*> Bishop::targets() {
    std::vector<Square*> targets;
    squaresForDirection({1, -1, 1, -1}, {1, 1, -1, -1}, targets);
    return targets;
}

std::vector<Square*> Queen::targets() {
    std::vector<Square*> targets;
    squaresForDirection({0, 1, 0, -1, 1, -1, 1, -1},
                        {-1, 0, 1, 0, 1, 1, -1, -1}, targets);
    return targets;
}

std::vector<Square*> King::targets() {
    std::vector<Square*> targets;
    filterValidSquares({1, 1, 1, 0, 0, -1, -1, -1}, {1, 0, -1, 1, -1, 1, 0, -1},
                       targets);
    return targets;
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
