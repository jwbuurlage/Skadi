#pragma once

#include <string>
#include <map>

#include <board/pieces.hpp>
#include <board/board.hpp>

namespace Skadi {

const static std::string rowNames = "abcdefgh";
const static std::string columnNames = "12345678";

const static std::map<char, Piece> whitePieceForLabel = {
    { 'r', Rook() },
    { 'b', Bishop() },
    { 'n', Knight() },
    { 'k', King() },
    { 'q', Queen() },
    { 'p', Pawn() }
};

const static std::map<char, Piece> blackPieceForLabel = {
    { 'R', Rook() },
    { 'B', Bishop() },
    { 'N', Knight() },
    { 'K', King() },
    { 'Q', Queen() },
    { 'P', Pawn() }
};

void setBoardfromFEN(Board& board, std::string fen) {
    unsigned int pos = 0;
    for (unsigned int row = 0; row < 8; ++row) {
        unsigned int col = 0;
        for (; fen[pos] != '/' && fen[pos] != ' '; ++pos) {
            std::cout << "fen[pos] = " << fen[pos] << std::endl;
            if ('1' <= fen[pos] && fen[pos] <= '9') {
                col += fen[pos] - '1';
            } else if (whitePieceForLabel.find(fen[pos]) !=
                       whitePieceForLabel.end()) {
                auto piece = whitePieceForLabel.at(fen[pos]);
                piece.setPosition(row, col);
                board.addPiece(Color::white, piece);
            } else if (blackPieceForLabel.find(fen[pos]) !=
                       blackPieceForLabel.end()) {
                auto piece = blackPieceForLabel.at(fen[pos]);
                piece.setPosition(row, col);
                board.addPiece(Color::black, piece);
            }
        }
        ++pos;
    }
}

std::string boardToFEN(Board& board) {
    return "";
}

void apply(Board& board, std::string move) {

}

} // namespace Skadi
