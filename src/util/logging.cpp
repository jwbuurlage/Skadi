#include "util/logging.hpp"

namespace Skadi {

const static std::map<ChessPiece, char> labelForPiece = {
    {ChessPiece::rook, 'r'},   {ChessPiece::bishop, 'b'},
    {ChessPiece::knight, 'n'}, {ChessPiece::king, 'k'},
    {ChessPiece::queen, 'q'},  {ChessPiece::pawn, 'p'},
    {ChessPiece::none, '?'}};

jw::Logger& operator<<(jw::Logger& logger, const Board& board) {
    std::array<std::string, board.getSize()> boardString{
        "-+-+-+-+", "+-+-+-+-", "-+-+-+-+", "+-+-+-+-",
        "-+-+-+-+", "+-+-+-+-", "-+-+-+-+", "+-+-+-+-"};

    auto toUpper = [](char c) { return c - 'a' + 'A'; };

    for (auto& p : board.getPieces()) {
        if (p->isCaptured())
            continue;
        boardString[board.getSize() - 1 - p->getRow()][p->getColumn()] =
            (p->getColor() == Color::white)
                ? toUpper(labelForPiece.at(p->getType()))
                : labelForPiece.at(p->getType());
    }

    logger << "\n";
    for (auto row : boardString) {
        logger << row << "\n";
    }

    return logger;
}

jw::Logger& operator<<(jw::Logger& logger, const Square& square) {
    logger << columnNames[square.column] << rowNames[square.row];
    return logger;
}

jw::Logger& operator<<(jw::Logger& logger, const Piece& piece) {
    logger << labelForPiece.at(piece.getType()) << " ("
           << columnNames[piece.getColumn()] << rowNames[piece.getRow()] << ")";

        return logger;
}

jw::Logger& operator<<(jw::Logger& logger, const Move& move) {
    auto toUpper = [](char c) { return c - 'a' + 'A'; };
    logger << std::string(1,
                          toUpper(labelForPiece.at(move.getPiece()->getType())))
           << columnNames[move.getPiece()->getColumn()]
           << rowNames[move.getPiece()->getRow()]
           << columnNames[move.getTarget()->column]
           << rowNames[move.getTarget()->row];

    return logger;
}
} // namespace Skadi
