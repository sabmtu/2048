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

    /**
     * Initializes vector of tiles with size of given number of tiles per side.
     * @param num_tiles_per_side size_t representing number of tiles per side of board.
     */
    GameEngine(size_t num_tiles_per_side);

    const vector<vector<Tile>>& GetTiles();
    void SetCurrentDirection(const Direction& direction);

    /**
     * Moves tiles in given direction.
     */
    void MoveTiles();

    /**
     * If tiles have finished moving in current direction, sets direction to still and generates a new tile.
     */
    void EndMovement();

private:
    //2d vector representing board of tiles
    vector<vector<Tile>> tiles_;

    //Details and size of tiles and board
    size_t num_tiles_per_side_;
    Direction current_direction_;

    //Empty tile
    const Tile kEmptyTile = Tile(0, "beige");

    /**
     * Methods to move and merge all tiles in corresponding directions.
     */
    void MoveTilesUp();
    void MoveTilesRight();
    void MoveTilesLeft();
    void MoveTilesDown();

    /**
     * Check if tile at given row and col can merge with adjacent tile in corresponding direction.
     * @param row size_t representing row
     * @param col size_t representing column
     * @return bool representing if the tile at given spot can merge with touching tile
     */
    bool CanMergeTileUp(size_t row, size_t col);
    bool CanMergeTileRight(size_t row, size_t col);
    bool CanMergeTileLeft(size_t row, size_t col);
    bool CanMergeTileDown(size_t row, size_t col);

    /**
     * Check if tiles for current direction from arrow key have finished moving.
     * @return bool representing if tiles have finished moving in given direction
     */
    bool HasFinishedMovingUp();
    bool HasFinishedMovingRight();
    bool HasFinishedMovingLeft();
    bool HasFinishedMovingDown();

    /**
     * Merges tile at given row and col with adjacent tile corresponding to current direction.
     * @param row size_t representing row of board
     * @param col size_t representing column of board
     */
    void MergeTiles(size_t row, size_t col);

    /**
     * Sets state of all tiles to unblocked so they can merge with tiles in next movement.
     */
    void FreeTilesForNextMove();

    /**
     * Randomly generates and adds new tile.
     */
    void AddNewTile();
};

}
