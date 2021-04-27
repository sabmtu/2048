#include <core/tile.h>

namespace game_2048 {

Tile::Tile() { }

Tile::Tile(size_t num, ci::Color color) {
    number_ = num;
    color_ = color;
}

const ci::Color &Tile::GetColor() const {
    return color_;
}

size_t Tile::GetNumber() const {
    return number_;
}

bool Tile::operator==(const Tile &tile) const {
    if (number_ != tile.GetNumber() || color_ != tile.GetColor()) {
        return false;
    }
    return true;
}

bool Tile::IsEmpty() const{
    return number_ == 0;
}


}