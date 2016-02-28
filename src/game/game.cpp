#include "game/game.hpp"

namespace Skadi {

std::vector<Piece*> Game::getActivePieces() { return activePieces; }

Board& Game::getBoard() { return board_; }
const Board& Game::getBoard() const { return board_; }

void Game::activate(Piece* piece) {
    activePieces.push_back(piece);
    activePiecesForColor[piece->getColor()].push_back(piece);
}

void Game::deactivate(Piece* piece) {
    activePieces.erase(
        std::remove(activePieces.begin(), activePieces.end(), piece),
        activePieces.end());

    activePiecesForColor[piece->getColor()].erase(
        std::remove(activePieces.begin(), activePieces.end(), piece),
        activePieces.end());
}

Color Game::colorToMove() const {
    return (halfMove_ % 2 == 1) ? Color::white : Color::black;
}

void Game::nextMove() {
    halfMove_ += 1;
    move_ = (halfMove_ - 1) / 2 + 1;
    fiftyMoves_ += 1;
}

int Game::getHalfMove() const { return halfMove_; }
void Game::setHalfMove(int halfMove) { halfMove_ = halfMove; }

void Game::resetFiftyMoves(int moves) { fiftyMoves_ = moves; }

CastlingRights& Game::getCastlingRights() { return castlingRights_; }

void Game::setEnPassentSquare(Square* square) { enPassentSquare = square; }
void Game::setMove(int move) { move_ = move; };


Piece* Game::locatePiece(ChessPiece type, Color color) const {
    for(auto piece : activePieces) {
        if (piece->getColor() == color && piece->getType() == type)
            return piece;
    }
    return nullptr;
}
} // namespace Skadi
