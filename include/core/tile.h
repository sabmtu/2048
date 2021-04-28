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

    //double GetMoveSpeed() const;
    const ci::Color& GetColor() const;
    size_t GetNumber() const;
    bool GetIsBlocked() const;
    void SetIsBlocked(bool set);
    bool IsEmpty() const;

    /**
     * Overload equality operator to check if two Tile objects are equal.
     * @param image const Tile reference representing Tile to be compared
     * @return bool representing whether or not the Tile values are all equal
     */
    bool operator==(const Tile& tile) const;
    //bool has_merged;

private:
    bool is_blocked_;
    size_t number_;
    ci::Color color_;

};

}
