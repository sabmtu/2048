#include <catch2/catch.hpp>
#include <visualizer/board.h>
#include <core/tile.h>

using game_2048::Board;
using game_2048::Tile;

TEST_CASE("Initialize board correctly") {
    Board board(glm::vec2(0,0), 4, 4);

}

