#include <catch2/catch.hpp>
#include <core/tile.h>
#include <core/game_engine.h>

using std::vector;
using game_2048::Tile;
using game_2048::GameEngine;

TEST_CASE("Game engine logic") {
    GameEngine game(3);

    REQUIRE(game.GetTiles().size() == 3);
    REQUIRE(game.GetTiles()[0].size() == 3);
    REQUIRE(game.GetTiles()[1].size() == 3);
    REQUIRE(game.GetTiles()[2].size() == 3);
}
