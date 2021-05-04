#pragma once

#include "cinder/gl/gl.h"
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

    enum GameState {
        ACTIVE, LOST, WON
    };

    const vector<vector<Tile>>& GetTiles();
    const size_t GetScore();
    const GameState& GetGameState();
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

    size_t score_;

    //State of the game
    GameState game_state_;

    //Empty tile
    const Tile kEmptyTile = Tile(0, "beige");
    const Tile kStartTile2 = Tile(2, ci::Color8u(250, 250, 242));
    const Tile kStartTile4 = Tile(4, ci::Color8u(255, 248, 232));

    //Store for tiles of each number to be different colors
    const std::map<size_t, ci::Color> kTileColors = {
            {2, ci::Color8u(250, 250, 242)},
            {4, ci::Color8u(255, 248, 232)},
            {8, ci::Color8u(255, 186, 102)},
            {16, ci::Color8u(249, 155, 65)},
            {32, ci::Color8u(234, 135, 98)},
            {64, ci::Color8u(249, 78, 50)},
            {128, ci::Color8u(250, 236, 159)},
            {256, ci::Color8u(248, 227, 110)},
            {512, ci::Color8u(254, 231, 102)},
            {1024, ci::Color8u(255, 223, 31)},
            {2048, ci::Color8u(253, 203, 50)},
            {4096, ci::Color8u(93, 187, 99)}
    };

    //bool variables to store result of HasFinishedMoving in each direction
    bool is_done_moving_up_;
    bool is_done_moving_right_;
    bool is_done_moving_left_;
    bool is_done_moving_down_;


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

    Tile MakeMergedTile(size_t row, size_t col);

    /**
     * Sets state of all tiles to unblocked so they can merge with tiles in next movement.
     */
    void FreeTilesForNextMove();

    /**
     * Randomly generates and adds new tile.
     */
    void AddNewTile();

    void CheckFinishMoving();
    bool HasFinishedMovingInDirection();
};

}
