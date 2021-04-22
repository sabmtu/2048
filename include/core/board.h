#pragma once
#include "cinder/gl/gl.h"
#include "tile.h"

namespace game_2048 {
    using std::vector;

class Board {



public:
    Board();

    /**
     * Constructor to initialize game board.
     * @param top_left_corner vec2 representing coords of top left corner of game board
     * @param num_tiles_per_side size_t representing dimension of game board
     * @param board_size double representing length of side of board in screen pixels
     */
    Board(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
          double board_size);

    //Getters
    const vector<Tile>& GetTiles();

    const glm::vec2& GetTopLeftCorner();
    const double GetTileSideLength();
    const double GetBoardSize();
    const size_t GetNumTilesPerSide();

    //Margin separating tiles when drawing
    const double kTileMargin = 10;

private:
    //Stores number tiles
    vector<Tile> tiles_;

    //Details and size of tiles and board
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;

};

}
