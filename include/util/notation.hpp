#pragma once

#include <string>
#include <map>

#include <board/pieces.hpp>
#include <board/board.hpp>
#include <board/moves.hpp>

namespace Skadi {

const static std::string rowNames = "abcdefgh";
const static std::string columnNames = "12345678";

void setBoardfromFEN(Board& board, std::string fen) {
    const static std::map<char, ChessPiece> whitePieceForLabel = {
        {'r', ChessPiece::rook},   {'b', ChessPiece::bishop},
        {'n', ChessPiece::knight}, {'k', ChessPiece::king},
        {'q', ChessPiece::queen},  {'p', ChessPiece::pawn}};

    const static std::map<char, ChessPiece> blackPieceForLabel = {
        {'R', ChessPiece::rook},   {'B', ChessPiece::bishop},
        {'N', ChessPiece::knight}, {'K', ChessPiece::king},
        {'Q', ChessPiece::queen},  {'P', ChessPiece::pawn}};

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

std::string boardToFEN(Board& board) { return ""; }

Move generateMove(Board& board, std::string move) {
    // treat castling separately
    // FIXME
    if (move == "o-o" || move == "O-O" || move == "0-0") {
        // castle short
    } else if (move == "o-o-o" || move == "O-O-O" || move == "0-0-0") {
        // castle long
    }

    static const std::map<char, ChessPiece> pieceForLabel = {
        {'R', ChessPiece::rook},
        {'N', ChessPiece::knight},
        {'B', ChessPiece::bishop},
        {'Q', ChessPiece::queen},
        {'K', ChessPiece::king}};

    // ignore check/checkmate
    if (move[move.size() - 1] == '+' || move[move.size() - 1] == '#') {
        move.pop_back();
    }

    ChessPiece pieceAfterPromotion = ChessPiece::none;

    // see if there is a promotion
    if ('A' <= move[move.size() - 1] && move[move.size() - 1] <= 'Z') {
        if (pieceForLabel.find(move[move.size() - 1]) != pieceForLabel.end()) {
            pieceAfterPromotion = pieceForLabel.at(move[move.size() - 1]);
        } else {
            JWLogError << "Unknown chess piece with label "
                       << move[move.size() - 1] << endLog;
        }
        move.pop_back();
    }

    // the final two characters *always* denote the target
    auto targetAsString = move.substr(move.size() - 2);
    auto targetSquare = board.getSquare(rowNames.find(targetAsString[1]),
                                        columnNames.find(targetAsString[0]));
    move.erase(move.size() - 2);

    // are we capturing
    bool capturing = false;
    if (move.size() > 0) {
        capturing = (move[move.size() - 1] == 'x');
        if (capturing)
            move.pop_back();
    }

    // is there a special piece involved?
    ChessPiece pieceToMove = ChessPiece::pawn;

    // possibly interpret piece
    if ('A' <= move[0] && move[0] <= 'Z') {
        if (pieceForLabel.find(move[0]) != pieceForLabel.end()) {
            pieceToMove = pieceForLabel.at(move[0]);
        } else {
            JWLogError << "Unknown chess piece with label " << move[0]
                       << endLog;
        }
        move = move.substr(1);
    }

    // disambiguiate
    // option 1: file of departure
    int departureColumn = -1;
    int departureRow = -1;
    if (move.size() > 0) {
        if ('a' <= move[0] && move[0] <= 'h') {
            departureColumn = columnNames.find(move[0]);
            if (move.size() > 1) {
                departureRow = rowNames.find(move[1]);
            }
        } else if ('1' <= move[0] && move[0] <= '8') {
            departureRow = rowNames.find(move[0]);
        }
    }

    Piece* piece = nullptr;
    for (auto& piece : board.getPieces())  {
        // does it haev the correct type?
        if (piece->getType() != pieceToMove)
            continue;

        // can it reach the target square
    }

    if (piece == nullptr) {
        JWLogError << "Could not find chess piece " << move[0]
                   << endLog;
    }


    // interpret PGN notation and make move
    return Move(&board, piece, targetSquare);
}

} // namespace Skadi
