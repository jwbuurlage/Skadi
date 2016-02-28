#include "game/board.hpp"
#include "game/pieces.hpp"
#include "util/logging.hpp"

namespace Skadi {

Board::Board() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
            squares_[i][j].row = i;
            squares_[i][j].column = j;
            squares_[i][j].piece = nullptr;
        }
    }
}

void Board::addPiece(std::unique_ptr<Piece>&& piece) {
    pieces_.push_back(std::move(piece));
}

bool Board::gameOver() const { return false; }

Square* Board::getSquare(int row, int col) { return &squares_[row][col]; }

Square* Board::getSquare(std::string description) {
    return getSquare(rowNames.find(description[1]),
                     columnNames.find(description[0]));
}

const std::vector<std::unique_ptr<Piece>>& Board::getPieces() const {
    return pieces_;
}

bool Board::squareUnderAttack(int row, int col, Color forColor, int halfMoveNumber) const {
    for (auto& piece : pieces_) {

        if (piece->isCaptured())
            continue;
        if (piece->getColor() == forColor)
            continue;
        if (piece->moveForTarget(row, col, halfMoveNumber)->isLegal()) {
            return true;
        }
    }
    return false;
}

} // namespace Skadi
