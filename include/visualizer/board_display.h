#pragma once

#include <vector>
#include <core/tile.h>
#include "cinder/gl/gl.h"

namespace game_2048 {
using std::vector;

class BoardDisplay {
public:
    /**
     * Constructor initializes board of tiles display.
     * @param top_left_corner 2d vector representing position of top left of board
     * @param num_tiles_per_side size_t representing number of tiles per side of the square board
     * @param board_size double representing length of board in screen pixels size
     */
    BoardDisplay(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
                 double board_size);

    /**
     * Displays the rectangle board outline.
     */
    void Draw();

    /**
     * Displays the given vectors of tiles covering the board.
     * @param tiles 2d vector representing rows and columns of all tiles on the board
     */
    void DrawNumberTiles(const vector<vector<Tile>>& tiles);


private:
    //Margin that separates tiles from other tiles and edge of board
    const double kTileMargin = 5;
    const size_t kStartTileNumBound = 8;
    const ci::Font kTileFont = ci::Font("Times New roman", 40);

    //Details and size of tiles and board
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;

};

}

