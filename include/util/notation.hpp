#pragma once

#include <string>
#include <map>

#include "board/pieces.hpp"
#include "board/board.hpp"
#include "board/moves.hpp"

#include "util/logging.hpp"

#include "types.hpp"

namespace Skadi {


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
                board.addPiece(std::move(
                    createPiece(&board, whitePieceForLabel.at(fen[pos]), row,
                                col, Color::white)));
                col += 1;
            } else if (blackPieceForLabel.find(fen[pos]) !=
                       blackPieceForLabel.end()) {
                board.addPiece(std::move(
                    createPiece(&board, blackPieceForLabel.at(fen[pos]), row,
                                col, Color::black)));
                col += 1;
            }
        }
        ++pos;
    }
}

std::string boardToFEN(Board& board) {
    JWLogWarning << "boardToFen() Not implemented yet" << endLog;
    return "";
}

Move generateMove(Board& board, std::string move, Color byColor, int moveNumber) {
    if (move.size() < 2) {
        JWLogError << "Invalid move submitted" << endLog;
        return Move(nullptr, nullptr, nullptr, -1);
    }

    // FIXME make an effort to see if the move is well formed

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

    Piece* boardPiece = nullptr;
    for (auto& piece : board.getPieces())  {
        // does it have the correct type?
        if (piece->getType() != pieceToMove)
            continue;

        // does it have the correct color?
        if (piece->getColor() != byColor)
            continue;

        // can it reach the target square?
        if (piece->canTarget(targetSquare->row, targetSquare->column)) {
            boardPiece = piece.get();
        }

        // does it have the correct credentials?
        // check with departureRow and departureCol
    }

    if (boardPiece == nullptr) {
        JWLogError << "Could not find chess piece " << move[0]
                   << endLog;
    }

    return Move(&board, boardPiece, targetSquare, moveNumber);
}

} // namespace Skadi
