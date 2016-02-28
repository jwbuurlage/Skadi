#include <catch.hpp>
#include <skadi.hpp>

TEST_CASE("basic movement", "[rules]") {
    SECTION("basic pawn movement") {
        Skadi::Game game;
        Skadi::Board board;
        Skadi::setBoardfromFEN(
            game, board,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        // try an illegal move
        auto e5w = Skadi::generateMove(game, "e5", Skadi::Color::white, 1);
        REQUIRE(!e5w->isLegal());

        // see if unmoved pawns can move double
        auto e4 = Skadi::generateMove(game, "e4", Skadi::Color::white, 1);
        REQUIRE(e4->isLegal());
        e4->make();

        auto e5 = Skadi::generateMove(game, "e5", Skadi::Color::black, 2);
        REQUIRE(e5->isLegal());
        e5->make();

        auto a4 = Skadi::generateMove(game, "a4", Skadi::Color::white, 3);
        REQUIRE(a4->isLegal());
        a4->make();

        // see if pawns can make single moves
        auto a6 = Skadi::generateMove(game, "a6", Skadi::Color::black, 4);
        REQUIRE(a6->isLegal());
        a6->make();
    }

    SECTION("en passant") {
        Skadi::Game game;
        Skadi::Board board;
        Skadi::setBoardfromFEN(
            game, board,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        Skadi::generateMove(game, "e4", Skadi::Color::white, 1)->make();
        Skadi::generateMove(game, "a5", Skadi::Color::black, 2)->make();
        Skadi::generateMove(game, "e5", Skadi::Color::white, 3)->make();
        Skadi::generateMove(game, "d5", Skadi::Color::black, 4)->make();
        auto enPassantLeft =
            Skadi::generateMove(game, "exd6", Skadi::Color::white, 5);
        REQUIRE(enPassantLeft->isLegal());
        enPassantLeft->make();
        REQUIRE(board.getSquare("d5")->piece == nullptr);
    }
}

// TEST_CASE("capturing", "[rules]") {}
// TEST_CASE("en passent", "[rules]") {}
TEST_CASE("castling", "[rules]") {
    SECTION("short") {
        Skadi::Game game;
        Skadi::Board board;
        Skadi::setBoardfromFEN(
            game, board,
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        Skadi::generateMove(game, "e4", Skadi::Color::white, 1)->make();
        Skadi::generateMove(game, "e5", Skadi::Color::black, 2)->make();
        Skadi::generateMove(game, "Be2", Skadi::Color::white, 3)->make();
        Skadi::generateMove(game, "a5", Skadi::Color::black, 4)->make();
        Skadi::generateMove(game, "Nf3", Skadi::Color::white, 5)->make();
        Skadi::generateMove(game, "a4", Skadi::Color::black, 6)->make();
        JWLogDebug << "before: " << endLog;
        auto castleShort = Skadi::generateMove(game, "o-o", Skadi::Color::white, 7);

        //REQUIRE(castleShort->isLegal());
    }
}
// TEST_CASE("check and checkmate", "[rules]") {}
// TEST_CASE("fifty moves rule", "[rules]") {}
