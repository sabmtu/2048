#pragma once

#include "cinder/gl/gl.h"
#include "board.h"


namespace game_2048 {

//Illustrate directions tiles will move
enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class GameEngine {
public:
    GameEngine();
    GameEngine(Board& board);

    /**
     * Moves tiles in given direction.
     * @param direction Direction representing which arrow key direction the tiles should move in
     */
    void MoveTiles(const Direction& direction);

    const Board& GetBoard();

private:
    Board board_;

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
