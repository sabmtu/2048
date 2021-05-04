#include <catch2/catch.hpp>
#include <core/tile.h>

using std::vector;
using game_2048::Tile;

TEST_CASE("Test tiles correctly") {
    Tile tile(0, ci::Color("white"));
    Tile tile_2(2, ci::Color("white"));

    SECTION("Check initialized tile is empty") {
        REQUIRE(tile.IsEmpty());
        REQUIRE(!tile_2.IsEmpty());
    }

    Tile same_tile(0, "white");
    Tile same_tile_2(2, "white");

    SECTION("Tile equality") {
        REQUIRE(tile == same_tile);
        REQUIRE(tile_2 == same_tile_2);
    }

    SECTION("Vector of tiles equality") {
        vector<Tile> vec;
        vec.push_back(tile);
        vec.push_back(tile_2);
        vector<Tile> vec2;
        vec2.push_back(same_tile);
        vec2.push_back(same_tile_2);
        REQUIRE(vec == vec2);
    }
}
