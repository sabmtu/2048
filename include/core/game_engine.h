#pragma once

#include "cinder/gl/gl.h"
//#include "board.h"
#include "tile.h"

namespace game_2048 {

using std::vector;

//Illustrate directions tiles will move
enum class Direction {
    STILL, UP, DOWN, LEFT, RIGHT
};

class GameEngine {
public:
    GameEngine();

    GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size);

    //GameEngine(Board& board);

    /**
     * Moves tiles in given direction.
     * @param direction Direction representing which arrow key direction the tiles should move in
     */
    void MoveTiles(const Direction& direction);

    const vector<Tile>& GetTiles();
    //const Board& GetBoard();

private:
    //Board board_;
    //Stores number tiles
    vector<Tile> tiles_;

    //Details and size of tiles and board
    glm::vec2 top_left_corner_;
    size_t num_tiles_per_side_;
    double tile_side_length_;
    double board_size_;

    Direction current_direction_;

    /**
     * Moves given tile in given direction until tile cannot move anymore.
     * @param tile Tile representing number tile being moved.
     * @param direction Direction representing direction tile should move.
     */
    void MoveInDirection(Tile& tile, const Direction& direction);

    /**
     * Checks if given tile has hit wall or another number tile and should stop moving.
     * @param tile Tile representing given tile moving
     * @return bool representing if has collided or not
     */
    bool HasCollidedWithWall(Tile& tile);
    bool HasCollidedWithTile(Tile& tile);
    //bool CheckTileMerge();
    //void MergeTiles();
};

}
