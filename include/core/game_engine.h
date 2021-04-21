#pragma once

#include <visualizer/board.h>
#include <visualizer/game_2048_app.h>
#include <core/tile.h>

namespace game_2048 {

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class GameEngine {
public:
    GameEngine();

    void MoveTiles(const Direction& direction);
    //const vector<vector<Tile>>& GetTiles();

private:
    vector<vector<Tile>> tiles_;
    Board board_;

    void MoveInDirection(Tile& tile, const Direction& direction);

    bool HasCollidedWithWall(Tile& tile);
    bool HasCollidedWithTile(Tile& tile);
    bool CheckTileMerge();
    void MergeTiles();
};

}
