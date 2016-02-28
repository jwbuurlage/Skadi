#include <string>
#include <sstream>
#include <map>

#include "util/notation.hpp"

namespace Skadi {

void setBoardfromFEN(Game& game, Board& board, std::string fen) {
    const static std::map<char, ChessPiece> whitePieceForLabel = {
        {'R', ChessPiece::rook},   {'B', ChessPiece::bishop},
        {'N', ChessPiece::knight}, {'K', ChessPiece::king},
        {'Q', ChessPiece::queen},  {'P', ChessPiece::pawn}};

    const static std::map<char, ChessPiece> blackPieceForLabel = {
        {'r', ChessPiece::rook},   {'b', ChessPiece::bishop},
        {'n', ChessPiece::knight}, {'k', ChessPiece::king},
        {'q', ChessPiece::queen},  {'p', ChessPiece::pawn}};

    int pos = 0;
    for (int row = 7; row >= 0; --row) {
        int col = 0;
        for (; fen[pos] != '/' && fen[pos] != ' '; ++pos) {
            if ('1' <= fen[pos] && fen[pos] <= '9') {
                col += fen[pos] - '1';
            } else if (whitePieceForLabel.find(fen[pos]) !=
                       whitePieceForLabel.end()) {
                board.addPiece(createPiece(&game, &board,
                                           whitePieceForLabel.at(fen[pos]), row,
                                           col, Color::white));
                col += 1;
            } else if (blackPieceForLabel.find(fen[pos]) !=
                       blackPieceForLabel.end()) {
                board.addPiece(createPiece(&game, &board,
                                           blackPieceForLabel.at(fen[pos]), row,
                                           col, Color::black));
                col += 1;
            }
        }
        ++pos;
    }

    Color activeColor = (fen[pos] == 'w') ? Color::white : Color::black;
    pos += 2;

    // either - or KQkq
    auto& castlingRights = game.getCastlingRights();
    while (fen[pos] != ' ') {
        switch (fen[pos]) {
        case '-':
            break;
        case 'K':
            castlingRights.whiteKingSide = true;
            break;
        case 'Q':
            castlingRights.whiteQueenSide = true;
            break;
        case 'k':
            castlingRights.blackKingSide = true;
            break;
        case 'q':
            castlingRights.blackQueenSide = true;
            break;
        }
        ++pos;
    }
    ++pos;

    // either - or square for en passent
    if (fen[pos] != '-') {
        auto squareAsString = fen.substr(pos, 2);
        auto square = board.getSquare(rowNames.find(squareAsString[1]),
                                      columnNames.find(squareAsString[0]));
        game.setEnPassentSquare(square);
        pos += 3;
    } else {
        pos += 2;
    }

    std::stringstream ss(fen.substr(pos));

    // half moves since pawn move or capture
    int halfMovesRule = 0;
    ss >> halfMovesRule;
    game.resetFiftyMoves(halfMovesRule);

    // moves
    int moves = 0;
    ss >> moves;
    game.setMove(moves);
    int halfMoves =
        (activeColor == Color::white) ? (moves - 1) * 2 + 1 : moves * 2;
    game.setHalfMove(halfMoves);
}

std::string boardToFEN(Board& board) {
    JWLogWarning << "boardToFen(): Not implemented yet" << endLog;
    return "";
}

std::unique_ptr<Move> generateMove(Game& game, std::string move, Color byColor,
                                   int halfMoveNumber) {
    Board& board = game.getBoard();

    // FIXME make a better effort to see if the move is not ill-formed to start
    // with
    if (move.size() < 2) {
        JWLogWarning << "Invalid move submitted" << endLog;
        return std::make_unique<NullMove>();
    }

    // treat castling separately
    auto king = (King*)(game.locatePiece(ChessPiece::king, byColor));
    if (move == "o-o" || move == "O-O" || move == "0-0") {
        return king->castleMove(halfMoveNumber, CastlingType::castle_short);
    } else if (move == "o-o-o" || move == "O-O-O" || move == "0-0-0") {
        return king->castleMove(halfMoveNumber, CastlingType::castle_long);
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
            JWLogWarning << "Unknown chess piece with label "
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
            JWLogWarning << "Unknown chess piece with label " << move[0]
                         << endLog;
        }
        move = move.substr(1);
    }


    if (pieceAfterPromotion != ChessPiece::none) {
        if (pieceToMove != ChessPiece::pawn) {
            JWLogWarning << "Invalid input, promotion only possible with pawn"
                         << endLog;
            return std::make_unique<NullMove>();
        }
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
    for (auto piece : game.getActivePieces()) {
        // does it have the correct type?
        if (piece->getType() != pieceToMove)
            continue;

        // does it have the correct color?
        if (piece->getColor() != byColor)
            continue;

        std::unique_ptr<Move> candidateMove;
        if (pieceAfterPromotion == ChessPiece::none) {
            // can it reach the target square?
             candidateMove = piece->moveForTarget(
                targetSquare->row, targetSquare->column, halfMoveNumber);
        } else {
            candidateMove = ((Pawn*)piece)
                                ->moveForTargetWithPromotion(
                                    targetSquare->row, targetSquare->column,
                                    halfMoveNumber, pieceAfterPromotion);
        }

        if (candidateMove->isLegal()) {
            return candidateMove;
        }

        // FIXME: does it have the correct credentials?
        // check with departureRow and departureCol
    }

    if (boardPiece == nullptr) {
        JWLogWarning << "Could not find chess piece for move " << move
                     << endLog;
    }

    return std::make_unique<Move>(&game, &board, boardPiece, targetSquare,
                                  halfMoveNumber);
}

} // namespace Skadi
