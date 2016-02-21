#include <catch.hpp>
#include <skadi.hpp>

TEST_CASE("basic movement", "[rules]") {
    SECTION("pawn movement") {
        Skadi::Game game;
        Skadi::Board board;
        Skadi::setBoardfromFEN(
            game, board,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        // see if indeed white is to start
        REQUIRE(game.colorToMove() == Skadi::Color::white);
    }
}

// TEST_CASE("capturing", "[rules]") {}
// TEST_CASE("en passent", "[rules]") {}
// TEST_CASE("castling", "[rules]") {}
// TEST_CASE("check and checkmate", "[rules]") {}
// TEST_CASE("fifty moves rule", "[rules]") {}
