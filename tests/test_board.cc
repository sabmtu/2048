#include <catch2/catch.hpp>
#include <core/tile.h>

using game_2048::Tile;

TEST_CASE("Initialize board correctly") {

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
        REQUIRE(tile.position_.y == 8);
    }

    SECTION("Move left") {
        tile.MoveLeft();
        REQUIRE(tile.position_.x == 8);
    }

}

