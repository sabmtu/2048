#pragma once

#include <vector>
#include <core/tile.h>
#include <core/board.h>
#include "cinder/gl/gl.h"

namespace game_2048 {
using std::vector;

class BoardDisplay {
public:
    BoardDisplay();
    BoardDisplay(const Board& board);
    void Draw();



private:
    Board board_;

    void DrawTiles();
};

}

