#pragma once

//#include <vector>
#include <core/tile.h>
#include "cinder/gl/gl.h"
#include <core/board.h>
#include <visualizer/game_2048_app.h>


namespace game_2048 {

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class GameEngine {
public:
    GameEngine();
    GameEngine(const glm::vec2& top_left_corner, size_t num_tiles_per_side,
               double board_size);
    void MoveTiles(const Direction& direction);
    void UpdateGame();

private:
    Board board_;
    BoardDisplay board_display_;

    void MoveInDirection(Tile& tile, const Direction& direction);

    bool HasCollidedWithWall(Tile& tile);
    bool HasCollidedWithTile(Tile& tile);
    //bool CheckTileMerge();
    //void MergeTiles();
};

}
