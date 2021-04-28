#include <catch2/catch.hpp>
#include <core/tile.h>
#include <core/game_engine.h>

using std::vector;
using game_2048::Tile;
using game_2048::GameEngine;

TEST_CASE("Game engine logic") {
    GameEngine game(3);

    SECTION("Initialize board vector") {
        REQUIRE(game.GetTiles().size() == 3);
        REQUIRE(game.GetTiles()[0].size() == 3);
        REQUIRE(game.GetTiles()[1].size() == 3);
        REQUIRE(game.GetTiles()[2].size() == 3);
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 2);
    }
}

TEST_CASE("Move Tiles") {
    GameEngine game(3);

    SECTION("Move Tiles Still") {
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 2);
    }

    SECTION("Move Tiles Down") {
        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 0);
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 2);
    }

    SECTION("Move Tiles Up") {
        game.SetCurrentDirection(game_2048::Direction::UP);
        game.MoveTiles();
        REQUIRE(game.GetTiles()[0][1].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 0);
    }

    SECTION("Move Tiles Right") {
        game.SetCurrentDirection(game_2048::Direction::RIGHT);
        game.MoveTiles();
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 0);
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 2);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 2);
    }

    SECTION("Move Tiles Left") {
        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 0);
        REQUIRE(game.GetTiles()[1][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 2);
    }
}
