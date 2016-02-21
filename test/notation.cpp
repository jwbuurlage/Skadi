#include <catch.hpp>
#include <skadi.hpp>

TEST_CASE("we can load games from FEN", "[notation]") {
    SECTION("standard game setup") {
        Skadi::Game game;
        Skadi::Board board;

        // load the board from FEN
        Skadi::setBoardfromFEN(
            game, board,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        // see if indeed white is to start
        REQUIRE(game.colorToMove() == Skadi::Color::white);

        // check if castling rights get set
        auto& castlingRights = game.getCastlingRights();
        REQUIRE(castlingRights.blackKingSide);
        REQUIRE(castlingRights.blackQueenSide);
        REQUIRE(castlingRights.whiteQueenSide);
        REQUIRE(castlingRights.whiteKingSide);

        // we check the position of a selection of pieces
        auto whiteKingSquare = board.getSquare(0, 4);
        REQUIRE(whiteKingSquare->piece != nullptr);
        REQUIRE(whiteKingSquare->piece->getType() == Skadi::ChessPiece::king);
        REQUIRE(whiteKingSquare->piece->getColor() == Skadi::Color::white);

        auto blackRookSquare = board.getSquare(7, 0);
        REQUIRE(blackRookSquare->piece != nullptr);
        REQUIRE(blackRookSquare->piece->getType() == Skadi::ChessPiece::rook);
        REQUIRE(blackRookSquare->piece->getColor() == Skadi::Color::black);
    }

    SECTION("empty board") {
        Skadi::Game game;
        Skadi::Board board;

        // load the board from FEN
        Skadi::setBoardfromFEN(game, board, "8/8/8/8/8/8/8/8 w - - 25 30");

        // see if indeed white is to start
        REQUIRE(game.colorToMove() == Skadi::Color::white);

        // check if castling rights get set
        auto& castlingRights = game.getCastlingRights();
        REQUIRE(!castlingRights.blackKingSide);
        REQUIRE(!castlingRights.blackQueenSide);
        REQUIRE(!castlingRights.whiteQueenSide);
        REQUIRE(!castlingRights.whiteKingSide);

        // check if move gets set right
        REQUIRE(game.getHalfMove() == 59);

        // see if no pieces get set
        REQUIRE(game.getActivePieces().empty());
    }

    SECTION("simple board") {
        Skadi::Game game;
        Skadi::Board board;

        // load the board from FEN
        Skadi::setBoardfromFEN(game, board, "8/8/8/4k3/6K1/8/8/8 b - - 25 30");

        // see if indeed black is to start
        REQUIRE(game.colorToMove() == Skadi::Color::black);
    }
}

// interpret SAN
TEST_CASE("we can make basic moves SAN", "[notation]") {
    SECTION("Can move pawn two forward initially") {
        Skadi::Game game;
        Skadi::Board board;
        Skadi::setBoardfromFEN(
            game, board,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        Skadi::generateMove(game, "e4", Skadi::Color::white, 1).make();

        // original piece is gone
        auto e2Square = board.getSquare("e2");
        REQUIRE(e2Square->piece == nullptr);

        // and it moved to correct place
        auto e4Square = board.getSquare("e4");
        REQUIRE(e4Square->piece != nullptr);
        REQUIRE(e4Square->piece->getType() == Skadi::ChessPiece::pawn);
        REQUIRE(e4Square->piece->getColor() == Skadi::Color::white);
    }
}

// interpret PGN
TEST_CASE("we can load PGN files", "[notation]") {}
