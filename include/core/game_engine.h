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
    GameEngine(size_t num_tiles_per_side);

    void SetCurrentDirection(const Direction& direction);

    /**
     * Moves tiles in given direction.
     */
    void MoveTiles();
    void EndMovement();

    const vector<vector<Tile>>& GetTiles();

private:
    vector<vector<Tile>> tiles_;

    //Details and size of tiles and board
    size_t num_tiles_per_side_;


    Direction current_direction_;

    const Tile kEmptyTile = Tile(0, "beige");


    void MoveTilesUp();
    void MoveTilesRight();
    void MoveTilesLeft();
    void MoveTilesDown();

    bool CanMergeTileUp(size_t row, size_t col);
    bool CanMergeTileRight(size_t row, size_t col);
    bool CanMergeTileLeft(size_t row, size_t col);
    bool CanMergeTileDown(size_t row, size_t col);

    //void MergeTilesUp();
    bool HasFinishedMovingUp();
    bool HasFinishedMovingRight();
    bool HasFinishedMovingLeft();
    bool HasFinishedMovingDown();
    void MergeTiles(size_t row, size_t col);

    void AddNewTile();
};

}
