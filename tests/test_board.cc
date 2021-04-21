#include <catch2/catch.hpp>
#include <visualizer/board_display.h>
#include <core/tile.h>

using game_2048::Board;
using game_2048::Tile;

TEST_CASE("Initialize board correctly") {
    Board board(glm::vec2(0,0), 4, 4);
    Tile tile (glm::vec2(10, 10), 2, "white");

    SECTION("Move down") {
        tile.MoveDown();
        REQUIRE(tile.position_.y == 12);
    }

    SECTION("Move right") {
        tile.MoveRight();
        REQUIRE(tile.position_.x == 12);
    }

    SECTION("Move up") {
        tile.MoveUp();
        REQUIRE(tile.position_.y == 10);
    }

    SECTION("Move left") {
        tile.MoveLeft();
        REQUIRE(tile.position_.x == 10);
    }

}

