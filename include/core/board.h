#pragma once
#include "cinder/gl/gl.h"
#include "game_engine.h"

namespace game_2048 {
    using std::vector;

class Board {



public:
    Board();
    Board(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
          double board_size);

    const vector<Tile>& GetTiles();

    const glm::vec2& GetTopLeftCorner();
    const double GetTileSideLength();
    const double GetBoardSize();
    const size_t GetNumTilesPerSide();
    const double kTileMargin = 10;

private:
    vector<Tile> tiles_;

    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;

};

}
