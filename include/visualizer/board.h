#pragma once

#include <vector>
#include <core/tile.h>
#include "cinder/gl/gl.h"

namespace game_2048 {
using std::vector;

class Board {
public:
    Board();
    Board(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
           double board_size);
    void Draw();

    const glm::vec2& GetTopLeftCorner();
    const double GetTileSideLength();
    const double GetBoardSize();
    const vector<vector<Tile>>& GetTiles();
    const size_t GetNumTilesPerSide();
    const double kTileMargin = 10;

private:
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;


    vector<vector<Tile>> tiles_;

    //void DrawTile(const Tile& tile);
};

}

