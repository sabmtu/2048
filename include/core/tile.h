#pragma once
#include "cinder/gl/gl.h"

namespace game_2048 {

class Tile {

public:
    Tile();

    /**
     * Constructor to initialize each number tile.
     * @param position vec2 representing coordinates of position vector
     * @param num size_t representing number of the tile
     * @param color Color of the number tile
     */
    Tile(glm::vec2 position, size_t num, ci::Color color);

    //position vector
    glm::vec2 position_;

    const ci::Color& GetColor() const;
    size_t GetNumber() const;

    //Methods to move tile
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();

    /**
     * Overload equality operator to check if two Tile objects are equal.
     * @param image const Tile reference representing Tile to be compared
     * @return bool representing whether or not the Tile values are all equal
     */
    bool operator==(const Tile& tile) const;

private:
    double kMoveSpeed = 2;
    size_t number_;
    ci::Color color_;

};

}
