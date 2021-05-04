#pragma once
#include "cinder/gl/gl.h"

namespace game_2048 {

class Tile {

public:
    Tile();

    /**
     * Constructor to initialize each number tile.
     * @param num size_t representing number of the tile
     * @param color Color of the number tile
     */
    Tile(size_t num, ci::Color color);

    //Getters and setters
    const ci::Color& GetColor() const;
    size_t GetNumber() const;
    bool GetIsBlocked() const;
    void SetIsBlocked(bool set);

    /**
     * Checks if tile is empty, meaning number is 0.
     * @return bool representing whether or not the number is 0
     */
    bool IsEmpty() const;

    /**
     * Overload equality operator to check if two Tile objects are equal.
     * @param image const Tile reference representing Tile to be compared
     * @return bool representing whether or not the Tile values are all equal
     */
    bool operator==(const Tile& tile) const;

private:
    //Represents if tile has already merged in one movement and thus is blocked from merging until new direction
    bool is_blocked_;

    //Represents number of the tile
    size_t number_;

    //Represents the color of the tile
    ci::Color color_;

};

}
