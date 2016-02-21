#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include "board.hpp"
#include "pieces.hpp"
#include "util/notation.hpp"

namespace Skadi {

class Game : public PieceObserver {
  public:
    std::vector<Piece*> getActivePieces() { return activePieces; }

    Board& getBoard() { return board_; }
    const Board& getBoard() const { return board_; }

    void activate(Piece* piece) override {
        activePieces.push_back(piece);
        activePiecesForColor[piece->getColor()].push_back(piece);
    }

    void deactivate(Piece* piece) override {
        activePieces.erase(
            std::remove(activePieces.begin(), activePieces.end(), piece),
            activePieces.end());

        activePiecesForColor[piece->getColor()].erase(
            std::remove(activePieces.begin(), activePieces.end(), piece),
            activePieces.end());
    }

  private:
    std::vector<Piece*> activePieces;
    std::map<Color, std::vector<Piece*>> activePiecesForColor = {
        {Color::white, {}}, {Color::black, {}} };

    Board board_;
};

} // namespace Skadi
