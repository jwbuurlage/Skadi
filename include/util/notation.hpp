#pragma once

#include <string>
#include <map>

#include <board/pieces.hpp>
#include <board/board.hpp>

namespace Skadi {

const static std::string rowNames = "abcdefgh";
const static std::string columnNames = "12345678";

const static std::map<char, ChessPiece> whitePieceForLabel = {
    {'r', ChessPiece::rook},   {'b', ChessPiece::bishop},
    {'n', ChessPiece::knight}, {'k', ChessPiece::king},
    {'q', ChessPiece::queen},  {'p', ChessPiece::pawn}};

const static std::map<char, ChessPiece> blackPieceForLabel = {
    {'R', ChessPiece::rook},   {'B', ChessPiece::bishop},
    {'N', ChessPiece::knight}, {'K', ChessPiece::king},
    {'Q', ChessPiece::queen},  {'P', ChessPiece::pawn}};

void setBoardfromFEN(Board& board, std::string fen) {
    unsigned int pos = 0;
    for (unsigned int row = 0; row < 8; ++row) {
        unsigned int col = 0;
        for (; fen[pos] != '/' && fen[pos] != ' '; ++pos) {
            if ('1' <= fen[pos] && fen[pos] <= '9') {
                col += fen[pos] - '1';
            } else if (whitePieceForLabel.find(fen[pos]) !=
                       whitePieceForLabel.end()) {
                board.addPiece(Color::white, whitePieceForLabel.at(fen[pos]),
                               row, col);
                col += 1;
            } else if (blackPieceForLabel.find(fen[pos]) !=
                       blackPieceForLabel.end()) {
                board.addPiece(Color::black, blackPieceForLabel.at(fen[pos]),
                               row, col);
                col += 1;
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
